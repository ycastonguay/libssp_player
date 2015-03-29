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
    public class SSPLoop
    {
        internal SSP_LOOP Struct;

        public Guid LoopId { get; set; }
        public Guid AudioFileId { get; set; }
        public string Name { get; set; }
        
        // database false
        //public string Index { get; set; }

        public long StartPositionBytes
        {
            get { return Struct.startPositionBytes; }
            set { Struct.startPositionBytes = value; }
        }

        public long EndPositionBytes
        {
            get { return Struct.endPositionBytes; }
            set { Struct.endPositionBytes = value; }
        }

        public long StartPositionMS { get; set; }
        public long StartPositionSamples { get; set; }
        public string StartPosition { get; set; }

        public long EndPositionMS { get; set; }
        public long EndPositionSamples { get; set; }
        public string EndPosition { get; set; }

        public long LengthBytes { get; set; }
        public long LengthMS { get; set; }
        public long LengthSamples { get; set; }
        public string Length { get; set; }

        public SSPLoop()
        {
            LoopId = Guid.NewGuid();
            StartPositionBytes = 0;
            StartPositionMS = 0;
            StartPositionSamples = 0;
            StartPosition = "0:00.000";
            EndPositionBytes = 0;
            EndPositionMS = 0;
            EndPositionSamples = 0;
            EndPosition = "0:00.000";
            LengthBytes = 0;
            LengthMS = 0;
            LengthSamples = 0;
            Length = "0:00.000";
        }
    }

    public enum SSPLoopSegmentType
    {
        Start = 0,
        End = 1
    }
}