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
    public class SSPEQPreset
    {
        internal SSP_EQPRESET Struct;

        public Guid Id
        {
            get { return new Guid(Struct.id); }
            set { Struct.id = value.ToString(); }
        }

        public string Name
        {
            get { return Struct.name; }
            set { Struct.name = value; }
        }

        public SSPEQPresetBand[] Bands
        {
            get
            {
                var array = new SSPEQPresetBand[Struct.bands.Length];
                for (int a = 0; a < Struct.bands.Length; a++)
                    array[a] = new SSPEQPresetBand(ref Struct.bands[a]);

                return array;
            }
            private set { }
        }
    }
}