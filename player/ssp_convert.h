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

__uint64_t convert_toSamples(__uint64_t milliseconds, int sampleRate);
__uint64_t convert_toSamplesFromBytes(__uint64_t bytes, int bitsPerSample, int channelCount);
__uint64_t convert_toMS(__uint64_t samples, int sampleRate);
__uint64_t convert_toBytes(__uint64_t samples, int bitRate, int channelCount);
float convert_msToTempo(float milliseconds);
float convert_tempoToMS(float tempo);
float convert_levelToDB(float level, float maxLevel);
void convert_toStringFromMS(__uint64_t milliseconds, char *str);
__uint64_t convert_toMSFromString(const char *string);
void convert_toString(char *str, __uint64_t bytes, int bitsPerSample, int channelCount, int sampleRate);

#endif /* defined(__player__ssp_convertaudio__) */