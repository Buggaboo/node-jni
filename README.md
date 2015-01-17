# node-jni
Access node.js on jvm/dalvik/ART, read: android.

Goals
-----

Not necessarily in this order:
* Write JNI binding -- DONE
* Build static library -- DONE
* Write android make `{Application, Android}.mk` file
* Test build
* Write android app to play with node.js, from a phone/tablet/wearable
* Release! (Profit?!?!?!?! Nah, collect bug reports and cultivate grey hair.)
* Redirect node stdout to Log.debug, or to TextView, see `fprintf(stdout...` and [this link](http://stackoverflow.com/questions/23352592/redirecting-stdin-and-stdout-of-c-program-in-android),
* Fix 'require()' issue, this might require hacking node.js
* Build *.so for arm, arm64, x86, x86_64, mips
* Secure the application, or at least think of strategies
* Repackage NodeJNI.java as jcenter or maven repository jar


News
----

_16 jan 2015_

Apparently, I wasn't paying much attention to how android handles NDK/JNI.
Android's `System.loadLibrary` only accepts *.so files, dynamic linking library / shared object, thingies.

The following does not work out-of-the-box, by changing one line `node.gyp`:
```javascript
{
    // ...
    'type': 'shared_library', // where it was 'executable' before
    // ...
}
```

It produces a broken so, that is missing some or all dependencies.

The next step, imho, is to write an mk file (android make), in the node workspace,
to generate a `libnode.so`.


But this is blocking:

```
[armeabi] SharedLibrary  : libnode.so
/android-ndk-r10/toolchains/arm-linux-androideabi-4.6/prebuilt/linux-x86_64/bin/../lib/gcc/arm-linux-androideabi/4.6/../../../../arm-linux-androideabi/bin/ld: ./obj/local/armeabi/objs/node/__/src/node_jni.o: in function Java_NodeJNI_start:/git-repositories/node/jni/../src/node_jni.cc:40: error: undefined reference to 'node::Start(int, char**)'
collect2: ld returned 1 exit status
make: *** [obj/local/armeabi/libnode.so] Error 1
```
