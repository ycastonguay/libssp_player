// Copyright © 2011-2015 Yanick Castonguay
//
// This file is part of Sessions, a music player for musicians.
//
// Sessions is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Sessions is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Sessions. If not, see <http://www.gnu.org/licenses/>.

using System;
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

        public string Driver
        {
            get { return Marshal.PtrToStringAnsi(Struct.driver); }
            set { Struct.driver = Marshal.StringToHGlobalAnsi(value); }
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

        public bool IsDefault
        {
            get { return Struct.isDefault; }
            set { Struct.isDefault = value; }
        }
    }
}