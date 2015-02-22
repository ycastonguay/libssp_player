using System.Runtime.InteropServices;

namespace org.sessionsapp.player
{
    public class SSPDevice
    {
        internal SSP_DEVICE Struct;

        public string Name
        {
            get { return Marshal.PtrToStringAnsi(Struct.name); }
            set { Struct.name = Marshal.StringToHGlobalAnsi(value); }
        }

        public int DeviceId
        {
            get { return Struct.deviceId; }
            set { Struct.deviceId = value; }
        }

        public bool IsInitialized
        {
            get { return Struct.isInitialized; }
            set { Struct.isInitialized = value; }
        }
    }
}
