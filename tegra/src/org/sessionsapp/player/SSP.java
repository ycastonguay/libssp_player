package org.sessionsapp.player;

public class SSP
{
    public static final int SSP_OK = 0;
    public static final int SSP_ERROR_UNKNOWN = 1;

    public static native int SSP_GetVersion();
    public static native int SSP_Init(String pathForPlugins);
    public static native int SSP_InitDevice(int device, int sampleRate, int bufferSize, int updatePeriod, boolean useFloatingPoint);
    public static native int SSP_FreeDevice();
    public static native int SSP_Free();

    static {
    	System.loadLibrary("bass");
    	System.loadLibrary("bass_fx");
    	System.loadLibrary("bassmix");
    	System.loadLibrary("bassenc");
        //System.loadLibrary("ssp_player");
    }
}