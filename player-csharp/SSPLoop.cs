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
using Sessions.Core.Attributes;

namespace org.sessionsapp.player
{
    public class SSPLoop
    {
        internal SSP_LOOP Struct;

        public Guid LoopId { get; set; }
        public Guid AudioFileId { get; set; }
        public string Name { get; set; }

        [DatabaseField(false)]
        public string Index { get; set; }

        public long StartPosition
        {
            get { return Struct.startPosition; }
            set { Struct.startPosition = value; }
        }

        public long EndPosition
        {
            get { return Struct.endPosition; }
            set { Struct.endPosition = value; }
        }

        public long StartPositionMS { get; set; }
        public long StartPositionSamples { get; set; }
        public string StartPositionStr { get; set; }

        public long EndPositionMS { get; set; }
        public long EndPositionSamples { get; set; }
        public string EndPositionStr { get; set; }
    }
}