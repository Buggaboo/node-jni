#POC: Embed node.js in an android application


On Linux (works on Linux and linux only, 22 jan 2015) Ubuntu in my case.

Build a [node.js](http://nodejs.org/) shared library (libnode.so) for embedding in android applications

You can find `node_jni.{cc,h}` in my project.

Apply these changes:

```diff
diff --git android-configure android-configure
index 7acb7f3..ffabab4 100755
--- android-configure
+++ android-configure
@@ -3,7 +3,7 @@
 export TOOLCHAIN=$PWD/android-toolchain
 mkdir -p $TOOLCHAIN
 $1/build/tools/make-standalone-toolchain.sh \
-    --toolchain=arm-linux-androideabi-4.7 \
+    --toolchain=arm-linux-androideabi-4.8 \
     --arch=arm \
     --install-dir=$TOOLCHAIN \
     --platform=android-9
@@ -12,8 +12,13 @@ export AR=arm-linux-androideabi-ar
 export CC=arm-linux-androideabi-gcc
 export CXX=arm-linux-androideabi-g++
 export LINK=arm-linux-androideabi-g++
+export PLATFORM=android # cares
+export OS=android # cares
 
 ./configure \
     --without-snapshot \
     --dest-cpu=arm \
-    --dest-os=android
+    --dest-os=android \
+    --without-npm
+    
+
diff --git configure configure
index 66cb312..bc8011d 100755
--- configure
+++ configure
@@ -652,6 +652,7 @@ def configure_v8(o):
   o['variables']['v8_optimized_debug'] = 0  # Compile with -O0 in debug builds.
   o['variables']['v8_random_seed'] = 0  # Use a random seed for hash tables.
   o['variables']['v8_use_snapshot'] = b(not options.without_snapshot)
+#  o['variables']['v8_compress_startup_data'] = "off"
 
   # assume shared_v8 if one of these is set?
   if options.shared_v8_libpath:
diff --git deps/cares/android-configure deps/cares/android-configure
index 5299e5c..1d1e142 100755
--- deps/cares/android-configure
+++ deps/cares/android-configure
@@ -3,7 +3,7 @@
 export TOOLCHAIN=$PWD/android-toolchain
 mkdir -p $TOOLCHAIN
 $1/build/tools/make-standalone-toolchain.sh \
-    --toolchain=arm-linux-androideabi-4.7 \
+    --toolchain=arm-linux-androideabi-4.8 \
     --arch=arm \
     --install-dir=$TOOLCHAIN \
     --platform=android-9
diff --git deps/cares/cares.gyp deps/cares/cares.gyp
index dfa35a2..9d1f265 100644
--- deps/cares/cares.gyp
+++ deps/cares/cares.gyp
@@ -1,4 +1,8 @@
 {
+  'variables': {
+    'OS%': '<!(echo $OS)',
+  },
+
   'target_defaults': {
     'conditions': [
       ['OS!="win"', {
@@ -151,6 +155,7 @@
         [ 'OS=="android"', {
           'include_dirs': [ 'config/android' ],
           'sources': [ 'config/android/ares_config.h' ],
+          'defines': [ 'ANDROID', '__ANDROID__', 'DONT_HAVE_GETSERVBYPORT_R', 'HAVE_ARPA_NAMESER_H' ],
         }],
         [ 'OS=="solaris"', {
           'include_dirs': [ 'config/sunos' ],
diff --git deps/cares/config/android/ares_config.h deps/cares/config/android/ares_config.h
index 9e6ef3c..7818ee8 100644
--- deps/cares/config/android/ares_config.h
+++ deps/cares/config/android/ares_config.h
@@ -116,7 +116,11 @@
 #define HAVE_GETNAMEINFO 1
 
 /* Define to 1 if you have the getservbyport_r function. */
-#define HAVE_GETSERVBYPORT_R 1
+#ifndef DONT_HAVE_GETSERVBYPORT_R
+#  define HAVE_GETSERVBYPORT_R 1
+#else
+#  undef HAVE_GETSERVBYPORT_R
+#endif
 
 /* Define to 1 if you have the `gettimeofday' function. */
 #define HAVE_GETTIMEOFDAY 1
diff --git deps/v8/build/android.gypi deps/v8/build/android.gypi
index 46ece08..9d33fc0 100644
--- deps/v8/build/android.gypi
+++ deps/v8/build/android.gypi
@@ -271,7 +271,6 @@
           '-Wl,-z,noexecstack',
           '-Wl,--gc-sections',
           '-Wl,-O1',
-          '-Wl,--as-needed',
         ],
       }],
     ],  # target_conditions
diff --git node.gyp node.gyp
index b59474e..d606c49 100644
--- node.gyp
+++ node.gyp
@@ -68,12 +68,13 @@
       'lib/zlib.js',
       'deps/debugger-agent/lib/_debugger_agent.js',
     ],
+    'java_home%': '<!(python -c "import os; dir=os.getenv(\'JAVA_HOME\', \'/usr/lib/jvm/java-7-openjdk-amd64\'); assert os.path.exists(os.path.join(dir, \'include/jni.h\')), \'Point \\$JAVA_HOME or the java_home gyp variable to a directory containing include/jni.h!\'; print dir")',
   },
 
   'targets': [
     {
       'target_name': 'node',
-      'type': 'executable',
+      'type': 'shared_library',
 
       'dependencies': [
         'node_js2c#host',
@@ -85,6 +86,7 @@
         'tools/msvs/genfiles',
         'deps/uv/src/ares',
         '<(SHARED_INTERMEDIATE_DIR)' # for node_natives.h
+        , '<(java_home)/include'
       ],
 
       'sources': [
@@ -99,7 +101,6 @@
         'src/node_file.cc',
         'src/node_http_parser.cc',
         'src/node_javascript.cc',
-        'src/node_main.cc',
         'src/node_os.cc',
         'src/node_v8.cc',
         'src/node_stat_watcher.cc',
@@ -151,6 +152,8 @@
         'src/util.h',
         'src/util-inl.h',
         'src/util.cc',
+        'src/node_jni.h',
+        'src/node_jni.cc',
         'deps/http_parser/http_parser.h',
         '<(SHARED_INTERMEDIATE_DIR)/node_natives.h',
         # javascript files to make for an even more pleasant IDE experience

```

Run these bash commands:

```bash
> git clone git@github.com:joyent/node.git
> git clone git@github.com:buggaboo/node-jni.git
> find node-jni/src-cpp/ -exec ln -s {} node/src/ \;
> cd node
> source ./android-configure
> mv ./android-toolchain/bin/python borkenPython && ln -s /usr/bin/python2.7 android-toolchain/bin/python
> virtualenv --system-site-packages venv # if missing: $(sudo pip install {git,...}) or $(sudo apt-get install {requests...})
> source ./venv/bin/activate
> make -j5
```

I arrived at `-j5` by counting the number of cores + 1, to build this. Your mileage may vary.

You need virtualenv to install python modules that get broken by the symbolic linking
of `/usr/lib/python`.

Source:
* [The commit that got this ball rolling](https://github.com/joyent/node/commit/5e4e8ec429381a8d1eebe31647e9daaaae42c54b)
* [Compile from the master branch from github](http://www.goland.org/nodejsonandroid/)
* [Support for android output](http://hanyugeekingstyle.blogspot.nl/2013/01/nodejs-for-android-with-consolelog.html)
* [Node stdout to android debug log](https://github.com/paddybyers/android-debuglog)
