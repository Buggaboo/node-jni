#POC: Embed node.js in an android application


On Linux (works on Linux and linux only, 14 jan 2015), Ubuntu in my case

Build a [node.js](http://nodejs.org/) shared library (libnode.so) for embedding in android applications

You can find `node_jni.{cc,h}` in my project.

Apply these changes:

```diff
diff --git android-configure android-configure
index 7acb7f3..aae0bf1 100755
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
diff --git node.gyp node.gyp
index 5454af2..bd5755d 100644
--- node.gyp
+++ node.gyp
@@ -68,12 +68,13 @@
       'lib/vm.js',
       'lib/zlib.js',
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
@@ -84,6 +85,7 @@
         'tools/msvs/genfiles',
         'deps/uv/src/ares',
         '<(SHARED_INTERMEDIATE_DIR)' # for node_natives.h
+        , '<(java_home)/include'
       ],
 
       'sources': [
@@ -147,6 +149,8 @@
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
> git clone git@github.com:buggaboo/node-jns.git
> find ln -s node-jni/src-cpp/ -exec ln -s {} node/src/ \;
> cd node # aka node workspace
> mv `which python` borkenPython && ln -s /usr/bin/python2.7 android-toolchain/bin/python
> virtualenv --system-site-packages venv
> source ./android-configure
> source ./venv/bin/activate
> make
```

You need virtualenv to install python modules that get broken by the symbolic linking
of `/usr/lib/python`.

Source:
* [Compile from the master branch from github](http://www.goland.org/nodejsonandroid/)
* [Support for android output](http://hanyugeekingstyle.blogspot.nl/2013/01/nodejs-for-android-with-consolelog.html)
* [Node stdout to android debug log](https://github.com/paddybyers/android-debuglog)
