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
    public class SSPMixer
    {
        internal SSP_MIXER Struct;

        public int BufferSize
        {
            get { return Struct.bufferSize; }
            set { Struct.bufferSize = value; }
        }

        public int UpdatePeriod
        {
            get { return Struct.updatePeriod; }
            set { Struct.updatePeriod = value; }
        }

        public int SampleRate
        {
            get { return Struct.sampleRate; }
            set { Struct.sampleRate = value; }
        }

        public bool UseFloatingPoint
        {
            get { return Struct.useFloatingPoint; }
            set { Struct.useFloatingPoint = value; }
        }
    }
}