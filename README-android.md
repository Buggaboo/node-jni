Embed node.js in an android application
=======================================

On Linux (works on Linux and linux only, 14 jan 2015)

build a static library in node.js for embedding in android application (libnode.a)

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
index 5454af2..b8590dd 100644
--- node.gyp
+++ node.gyp
@@ -73,7 +73,7 @@
   'targets': [
     {
       'target_name': 'node',
-      'type': 'executable',
+      'type': 'static_library',
 
       'dependencies': [
         'node_js2c#host',
```

Run these bash commands:

```bash
> git clone ...node.js on github...
> cd node
> source ./android-configure $ANDROID_NDK && make
> mv `which python` borkenPython && ln -s /usr/bin/python2.7 android-toolchain/bin/python
```

Source:
* [Compile from the master branch from github](http://www.goland.org/nodejsonandroid/)
* [Support for android output](http://hanyugeekingstyle.blogspot.nl/2013/01/nodejs-for-android-with-consolelog.html)
* [Node stdout to android debug log](https://github.com/paddybyers/android-debuglog)
