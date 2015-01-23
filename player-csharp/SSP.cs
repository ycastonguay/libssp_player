using System;
using System.Runtime.InteropServices;

namespace playersampleiosxamarin
{
    public static class SSP
    {
#if IOS
        public const string DllImportValue = "__Internal";
        public const string DllImportValueFx = "__Internal";
#elif ANDROID
        public const string DllImportValue = "libbass.so";
        public const string DllImportValueFx = "libbass_fx.so";
#endif

        [DllImport (DllImportValue)]
        public static extern int SSP_GetVersion();

        [DllImport (DllImportValue)]
        public static extern int SSP_Init(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);

//        [DllImport (DllImportValue)]
//        public static extern int SSP_GetDevice();

        [DllImport (DllImportValue)]
        public static extern long SSP_GetPosition();
        [DllImport (DllImportValue)]
        public static extern int SSP_SetPosition(long position);


        [DllImport (DllImportValue)]
        public static extern int SSP_Play();
        [DllImport (DllImportValue)]
        public static extern int SSP_Pause();
        [DllImport (DllImportValue)]
        public static extern int SSP_Stop();
        [DllImport (DllImportValue)]
        public static extern int SSP_Previous();
        [DllImport (DllImportValue)]
        public static extern int SSP_Next();
        [DllImport (DllImportValue)]
        public static extern int SSP_GoTo(int index);

        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_AddItem(string filePath);
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_InsertItemAt(string filePath, int index);
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_RemoveItemAt(int index);
//        [DllImport (DllImportValue)]
//        public static extern int SSP_Playlist_GetItemAt(int index);
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_Clear();
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_GetCount();
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_GetCurrentIndex();

        public static int SSP_OK = 0;
        public static int SSP_ERROR_UNKNOWN = 1;
    }
}
