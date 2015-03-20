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
#include <stdint.h>
#include "ssp_structs.h"

uint64_t convert_toSamples(uint64_t milliseconds, int sampleRate);
uint64_t convert_toSamplesFromBytes(uint64_t bytes, int bitsPerSample, int channelCount);
uint64_t convert_toMS(uint64_t samples, int sampleRate);
uint64_t convert_toBytes(uint64_t samples, int bitRate, int channelCount);
float convert_msToTempo(float milliseconds);
float convert_tempoToMS(float tempo);
float convert_levelToDB(float level, float maxLevel);
void convert_toStringFromMS(uint64_t milliseconds, char *str);
uint64_t convert_toMSFromString(const char *string);
void convert_toString(char *str, uint64_t bytes, int bitsPerSample, int channelCount, int sampleRate);
void convert_toPeakInfo(SSP_PEAKINFO* peakInfo, void* waveDataLeft, void* waveDataRight, int length, bool convertNegativeToPositive);

#endif /* defined(__player__ssp_convertaudio__) */
