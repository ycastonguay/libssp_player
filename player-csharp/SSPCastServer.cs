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
    public class SSPCastServer
    {
        internal SSP_CAST_SERVER Struct;

        public string Name
        {
            get { return Marshal.PtrToStringAnsi(Struct.name); }
            set { Struct.name = Marshal.StringToHGlobalAnsi(value); }
        }

        public string Url
        {
            get { return Marshal.PtrToStringAnsi(Struct.url); }
            set { Struct.url = Marshal.StringToHGlobalAnsi(value); }
        }

        public string Password
        {
            get { return Marshal.PtrToStringAnsi(Struct.password); }
            set { Struct.password = Marshal.StringToHGlobalAnsi(value); }
        }

        public int Bitrate
        {
            get { return Struct.bitrate; }
            set { Struct.bitrate = value; }
        }
    }
}