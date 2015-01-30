using System;
using System.Runtime.InteropServices;

namespace org.sessionsapp.player
{
    // Only for testing purposes, will be removed later
    public static class BASS
    {
#if IOS
        public const string DllImportValue = "__Internal";
        public const string DllImportValueFx = "__Internal";
#elif ANDROID
        public const string DllImportValue = "libbass.so";
        public const string DllImportValueFx = "libbass_fx.so";
#endif
        
        [DllImport (DllImportValue)]
        public static extern int BASS_ErrorGetCode();
        [DllImport (DllImportValue)]
        public static extern int BASS_Init(int device, int frequency);
        [DllImport (DllImportValue)]
        public static extern int BASS_Free();
        [DllImport (DllImportValue)]
        public static extern bool BASS_Start();
        [DllImport (DllImportValue)]
        public static extern bool BASS_Pause();
        [DllImport (DllImportValue)]
        public static extern bool BASS_Stop();
    }
}
