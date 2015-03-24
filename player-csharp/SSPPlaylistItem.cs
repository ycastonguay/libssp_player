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

using System.Runtime.InteropServices;

namespace org.sessionsapp.player
{
    public class SSPPlaylistItem
    {
        internal SSP_PLAYLISTITEM Struct;

        public int Id
        {
            get { return Struct.id; }
            set { Struct.id = value; }
        }    

        public int BitsPerSample
        {
            get { return Struct.bitsPerSample; }
            set { Struct.bitsPerSample = value; }
        }    

        public int Channel
        {
            get { return Struct.channel; }
            set { Struct.channel = value; }
        }    

        public string FilePath
        {
            get { return Marshal.PtrToStringAnsi(Struct.filePath); }
            set { Struct.filePath = Marshal.StringToHGlobalAnsi(value); }
        }

        public string AudioFileId
        {
            get { return Marshal.PtrToStringAnsi(Struct.audioFileId); }
            set { Struct.audioFileId = Marshal.StringToHGlobalAnsi(value); }
        }

        public bool IsLoaded
        {
            get { return Struct.isLoaded; }
            set { Struct.isLoaded = value; }
        }

        public long Length
        {
            get { return Struct.length; }
            set { Struct.length = value; }
        }    

        public int NumberOfChannels
        {
            get { return Struct.numberOfChannels; }
            set { Struct.numberOfChannels = value; }
        }    

        public int SampleRate
        {
            get { return Struct.sampleRate; }
            set { Struct.sampleRate = value; }
        }    
    }
}