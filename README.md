# node-jni
Access node.js on jvm/dalvik/ART, read: android.

Goals
-----

Not necessarily in this order:
* Write JNI binding -- DONE
* Build static library -- DONE
* Write android make *.mk file
* Test build
* Write android app to play with node.js, from a phone/tablet/wearable
* Release! (Profit?!?!?!?! Nah, collect bug reports and cultivate grey hair.)
* Redirect node stdout to Log.debug, or to TextView
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

