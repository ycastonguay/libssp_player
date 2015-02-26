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

namespace org.sessionsapp.player
{
    public class SSPPosition
    {
        internal SSP_POSITION Struct;

        public long Bytes
        {
            get { return Struct.bytes; }
            set { Struct.bytes = value; }
        }

        public long MS
        {
            get { return Struct.ms; }
            set { Struct.ms = value; }
        }

        public long Samples
        {
            get { return Struct.samples; }
            set { Struct.samples = value; }
        }

        public string Str
        {
            get { return Struct.str; }
            set { Struct.str = value; }
        }

        public static SSPPosition Empty = new SSPPosition() { Bytes = 0, MS = 0, Samples = 0, Str = "0:00.000" };
    }
}