# node-jni
Access node.js on jvm/dalvik/ART, read: android.

General idea
------------

I work towards the day when the back end nodejs engineer can
code the communication plumbing for the (android) mobile front end...

Goals
-----

Not necessarily in this order:
* Build shared library -- DONE
* Redirect node stdout to Log.debug, or to TextView, see `fprintf(stdout...` and [this link](http://stackoverflow.com/questions/23352592/redirecting-stdin-and-stdout-of-c-program-in-android),
* Write JNI binding, aka borrow from [joeferner/node-java](https://github.com/joeferner/node-java) and [android-cpp-sdk](https://code.google.com/p/android-cpp-sdk/)
* Write android app to play with node.js, from a phone/tablet/wearable
* Release! Profit?!?!?!?! Nah, collect bug reports and cultivate grey hair.
* Fix 'require()' issue, this might require hacking node.js
* Build *.so for arm, arm64, x86, x86_64, mips
* Secure the application, or at least think of strategies
* Repackage NodeJNI.java as jcenter or maven repository jar


News
----

_22 jan 2015_

Brainfart: I wanna play with [lzham compression](https://code.google.com/p/lzham/). Maybe something for [IO.js](https://iojs.org).

I should make IO.js embeddable in android too.


_22 jan 2015_

If applied [my patch](android-shared-lib.patch) can fix [nodejs master branch](https://github.com/joyent/node) to
build a shared library for Android.

Don't be alarmed by:

```
01-22 03:41:21.721  10819-10819/nl.sison.android.node_jni A/libc﹕ ../deps/uv/src/unix/proctitle.c:53: uv_setup_args: assertion "process_title.len + 1 == size" failed
01-22 03:41:21.721  10819-10819/nl.sison.android.node_jni A/libc﹕ Fatal signal 6 (SIGABRT) at 0x00002a43 (code=-6), thread 10819 (ndroid.node_jni)
```

At least we know `node::Start` is getting called.

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
