package nl.sison.android.nodejni;

/**
 * Note: Android only allows one JVM process per app
 * Tasks are a different matter,
 * hence the Singleton.
 *
 * TODO put this in a jar and gradleify and mavenify
 * Maybe just contribute it back to node.js,
 * just slap on an MIT and Joylent licence
 * and call it a day.
 */
public class NodeJNI {

    static
    {
        System.loadLibrary("node");
    }

    private NodeJNI () { /* Singleton */ }

    /** TODO match signature of node::Start(int, char[][]) */
    public static native int start(int argc, String[] argv);

/*
    public void exit()
    {

    }
*/

}


