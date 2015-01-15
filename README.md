# node-jni
Access node.js on jvm/dalvik/ART via a static library

Goals
-----
1. Build static library -- DONE
2. Write JNI binding
3. Write android app to play with node.js, from a phone/tablet/wearable
4. Redirect node stdout to Log.debug
5. Fix 'require()' issue, this might require hacking node.js
6. Secure the application, or at least think of strategies
7. Repackage NodeJNI.java as jcenter or maven repository jar

FAQ
---

Why static?

Because the dynamic lib did not build





