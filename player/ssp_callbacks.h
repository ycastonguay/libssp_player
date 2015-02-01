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

#ifndef player_callbacks_h
#define player_callbacks_h

//typedef void (CALLBACK GELLOPROC)(HSYNC handle, DWORD channel, DWORD data, void *user);
//typedef void (CALLBACK JELLOPROC)(int hello, float world);
//event LoopPlaybackStarted OnLoopPlaybackStarted;
//event LoopPlaybackStopped OnLoopPlaybackStopped;
//event PlaylistEnded OnPlaylistEnded;
//event PlaylistIndexChanged OnPlaylistIndexChanged;
//event AudioInterrupted OnAudioInterrupted;
//event BPMDetected OnBPMDetected;
//event SegmentIndexChanged OnSegmentIndexChanged;

typedef void (*player_log_cb)(void *user, const char* str);
typedef void (*player_playlistindexchanged_cb)(void *user);

#endif
