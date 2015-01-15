package nl.sison.android.node_jni;

/**
 * Note: Android only allows one JVM process per app
 * Tasks are a different matter.
 */
public class NodeJNI extends {

    static
    {
        // Load libs/libnode.a
        System.loadLibrary("node");
    }

    private NodeJNI () { /* Singleton */ }

    /** TODO match signature of node::Start(int, char[][]) */
    public native start(String[] s)
    {
        
    }

    public void exit()
    {

    }

}


