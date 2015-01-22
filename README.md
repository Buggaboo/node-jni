# node-jni
Access node.js on jvm/dalvik/ART, read: android.

General idea
------------

I work towards the day when the back end nodejs engineer can write the
code to do the communication plumbing for the (android) mobile front end...

Goals
-----

Not necessarily in this order:
* Build shared library -- DONE
* Write JNI binding, aka borrow from [joeferner/node-java](https://github.com/joeferner/node-java)
* Write android app to play with node.js, from a phone/tablet/wearable
* Release! Profit?!?!?!?! Nah, collect bug reports and cultivate grey hair.
* Redirect node stdout to Log.debug, or to TextView, see `fprintf(stdout...` and [this link](http://stackoverflow.com/questions/23352592/redirecting-stdin-and-stdout-of-c-program-in-android),
* Fix 'require()' issue, this might require hacking node.js
* Build *.so for arm, arm64, x86, x86_64, mips
* Secure the application, or at least think of strategies
* Repackage NodeJNI.java as jcenter or maven repository jar


News
----

_22 jan 2015_

If applied [my patch](android-shared-lib.patch) can fix [nodejs master branch](https://github.com/joyent/node) to
build a shared library for Android.

The next step would be to write callbacks for nodejs <-> android I/O. Stay tuned for more updates.

_19 jan 2015_

The function calls were being mangled beyond all recognition, due to
the deps being compiled with standard armeabi toolchain version 4.6
getting mixed with version 4.8.

The dependencies were also getting mangled badly due to this reason.

A patch for all the required changes will be released soon.

See: [README-android.md](https://github.com/Buggaboo/node-jni/blob/master/README-android.md).

Update: found [this](https://code.google.com/p/chromium/issues/detail?id=61430).
The `--as-needed` compiler switch might be disregarding stuff in the build prematurely.


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
