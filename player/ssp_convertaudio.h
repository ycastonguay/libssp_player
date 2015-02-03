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

#ifndef __player__ssp_convertaudio__
#define __player__ssp_convertaudio__

#include <stdio.h>

__uint64_t convertAudio_toSamples(__uint64_t milliseconds, int sampleRate);
__uint64_t convertAudio_toSamplesFromBytes(__uint64_t bytes, int bitsPerSample, int channelCount);
__uint64_t convertAudio_toMS(__uint64_t samples, int sampleRate);
__uint64_t convertAudio_toBytes(__uint64_t samples, int bitRate, int channelCount);
float convertAudio_msToTempo(float milliseconds);
float convertAudio_tempoToMS(float tempo);
float convertAudio_levelToDB(float level, float maxLevel);
char* convertAudio_toStringFromMS(__uint64_t milliseconds);
__uint64_t convertAudio_toMSFromString(const char* string);
char* convertAudio_toString(__uint64_t bytes, int bitsPerSample, int channelCount, int sampleRate);

#endif /* defined(__player__ssp_convertaudio__) */
