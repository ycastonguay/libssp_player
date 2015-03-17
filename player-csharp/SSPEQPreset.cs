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
    public class SSPEQPreset
    {
        internal SSP_EQPRESET Struct;

        private string Id
        {
            get { return Marshal.PtrToStringAnsi(Struct.id); }
            set { Struct.id = Marshal.StringToHGlobalAnsi(value); }
        }

        public Guid EQPresetId
        {
            get { return new Guid(Id); }
            set { Id = value.ToString(); }
        }

        public string Name
        {
            get { return Marshal.PtrToStringAnsi(Struct.name); }
            set { Struct.name = Marshal.StringToHGlobalAnsi(value); }
        }

        public SSPEQPresetBand[] Bands
        {
            get
            {
                var array = new SSPEQPresetBand[Struct.bands.Length];
                for (int a = 0; a < Struct.bands.Length; a++)
                    array[a] = new SSPEQPresetBand(this, a);

                return array;
            }
            private set { }
        }

        // These are for saving gain values to database
        public float Gain0 { get { return Bands[0].Gain; } set { Bands[0].Gain = value; } }
        public float Gain1 { get { return Bands[1].Gain; } set { Bands[1].Gain = value; } }
        public float Gain2 { get { return Bands[2].Gain; } set { Bands[2].Gain = value; } }
        public float Gain3 { get { return Bands[3].Gain; } set { Bands[3].Gain = value; } }
        public float Gain4 { get { return Bands[4].Gain; } set { Bands[4].Gain = value; } }
        public float Gain5 { get { return Bands[5].Gain; } set { Bands[5].Gain = value; } }
        public float Gain6 { get { return Bands[6].Gain; } set { Bands[6].Gain = value; } }
        public float Gain7 { get { return Bands[7].Gain; } set { Bands[7].Gain = value; } }
        public float Gain8 { get { return Bands[8].Gain; } set { Bands[8].Gain = value; } }
        public float Gain9 { get { return Bands[9].Gain; } set { Bands[9].Gain = value; } }
        public float Gain10 { get { return Bands[10].Gain; } set { Bands[10].Gain = value; } }
        public float Gain11 { get { return Bands[11].Gain; } set { Bands[11].Gain = value; } }
        public float Gain12 { get { return Bands[12].Gain; } set { Bands[12].Gain = value; } }
        public float Gain13 { get { return Bands[13].Gain; } set { Bands[13].Gain = value; } }
        public float Gain14 { get { return Bands[14].Gain; } set { Bands[14].Gain = value; } }
        public float Gain15 { get { return Bands[15].Gain; } set { Bands[15].Gain = value; } }
        public float Gain16 { get { return Bands[16].Gain; } set { Bands[16].Gain = value; } }
        public float Gain17 { get { return Bands[17].Gain; } set { Bands[17].Gain = value; } }

        public SSPEQPreset()
        {
            Struct.bands = new SSP_EQPRESETBAND[18];
            Reset();
        }

        public void Reset()
        {
            SSP.SSP_ResetEQPreset(ref Struct);
        }
    }
}