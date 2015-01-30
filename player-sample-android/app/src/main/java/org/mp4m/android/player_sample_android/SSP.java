//package org.sessionsapp.player;
package org.mp4m.android.player_sample_android;

public class SSP
{
    public static final int SSP_OK = 0;
    public static final int SSP_ERROR_UNKNOWN = 1;

    public static native int SSP_Init();

    static {
        System.loadLibrary("ssp_player");
    }
}