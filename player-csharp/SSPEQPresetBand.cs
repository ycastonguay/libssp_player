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
    public class SSPEQPresetBand
    {
        private SSPEQPreset _preset;
        private int _bandIndex;

        public float Center
        {
            get { return _preset.Struct.bands[_bandIndex].center; }
            set { _preset.Struct.bands[_bandIndex].center = value; }
        }

        public string Label
        {
            get { return Marshal.PtrToStringAnsi(_preset.Struct.bands[_bandIndex].label); }
            set { _preset.Struct.bands[_bandIndex].label = Marshal.StringToHGlobalAnsi(value); }
        }

        public float Bandwidth
        {
            get { return _preset.Struct.bands[_bandIndex].bandwidth; }
            set { _preset.Struct.bands[_bandIndex].bandwidth = value; }
        }

        public float Gain
        {
            get { return _preset.Struct.bands[_bandIndex].gain; }
            set { _preset.Struct.bands[_bandIndex].gain = value; }
        }

        public float Q
        {
            get { return _preset.Struct.bands[_bandIndex].q; }
            set { _preset.Struct.bands[_bandIndex].q = value; }
        }

        public SSPEQPresetBand(SSPEQPreset preset, int bandIndex)
        {
            // Use the reference to the SSPEQPreset class which contains the SSP_EQPRESET struct;
            // We can't use the struct as it will copy the values instead of using a ref
            _preset = preset;
            _bandIndex = bandIndex;
        }
    }
}