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

#include <math.h>
#include <stdbool.h>
#include "ssp_convert.h"
#include "ssp_structs.h"

uint64_t convert_toSamples(uint64_t milliseconds, int sampleRate) {
    return milliseconds * (sampleRate / 1000);
}

uint64_t convert_toSamplesFromBytes(uint64_t bytes, int bitsPerSample, int channelCount) {
    return bytes * 8 / bitsPerSample / channelCount;
}

uint64_t convert_toMS(uint64_t samples, int sampleRate) {
    return samples * 1000 / sampleRate;
}

uint64_t convert_toBytes(uint64_t samples, int bitRate, int channelCount) {
    return samples * bitRate * channelCount / 8;
}

float convert_msToTempo(float milliseconds) {
    return (60.0f / milliseconds) * 1000;
}

float convert_tempoToMS(float tempo) {
    return 60000.0f / tempo;
}

float convert_levelToDB(float level, float maxLevel) {
    return 20.0f * log10f(level / maxLevel);
}

void convert_toStringFromMS(uint64_t milliseconds, char *str) {
    uint64_t pos = milliseconds;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int ms = 0;

    if (pos >= 3600000)
    {
        hours = (int)pos / 3600000;
        pos %= 3600000;
    }
    if (pos >= 60000)
    {
        minutes = (int)pos / 60000;
        pos %= 60000;
    }
    if (pos >= 1000)
    {
        seconds = (int)pos / 1000;
        pos %= 1000;
    }
    ms = (int)pos;

    if(hours > 0) {
        sprintf(str, "%01d:%02d:%02d.%03d", hours, minutes, seconds, ms);
    }
    else {
        sprintf(str, "%01d:%02d.%03d", minutes, seconds, ms);
    }
}

uint64_t convert_toMSFromString(const char *string) {
    //    string strHours = String.Empty;
//    string strMinutes = String.Empty;
//    string strSeconds = String.Empty;
//    string strMilliseconds = String.Empty;
//
//    if(string.IsNullOrEmpty(position))
//        return 0;
//
//    string[] positionSplit = position.Split(':');
//    if (positionSplit.Length == 2)
//    {
//        string[] positionSplit2 = positionSplit[1].Split('.');
//        strMinutes = positionSplit[0];
//        strSeconds = positionSplit2[0];
//        strMilliseconds = positionSplit2[1];
//    }
//    if (positionSplit.Length == 3)
//    {
//        string[] positionSplit2 = positionSplit[2].Split('.');
//        strHours = positionSplit[0];
//        strMinutes = positionSplit[1];
//        strSeconds = positionSplit2[0];
//        strMilliseconds = positionSplit2[1];
//    }
//
//    int hours = 0;
//    Int32.TryParse(strHours, out hours);
//
//    int minutes = 0;
//    Int32.TryParse(strMinutes, out minutes);
//
//    int seconds = 0;
//    Int32.TryParse(strSeconds, out seconds);
//
//    int milliseconds = 0;
//    Int32.TryParse(strMilliseconds, out milliseconds);
//
//    return milliseconds + (seconds * 1000) + (minutes * 1000 * 60) + (hours * 1000 * 60 * 60);
    return 0;
}

void convert_toString(char *str, uint64_t bytes, int bitsPerSample, int channelCount, int sampleRate) {
    uint64_t samples = convert_toSamplesFromBytes(bytes, bitsPerSample, channelCount);
    uint64_t milliseconds = convert_toMS(samples, sampleRate);
    convert_toStringFromMS(milliseconds, str);
}

void convert_toPeakInfo(SSP_PEAKINFO* peakInfo, void* waveDataLeft, void* waveDataRight, int length, bool convertNegativeToPositive) {
    // Watch out when using this function, if P/Invoke calls this method in a secondary thread, is this running on the same thread or on the main thread?
    float* dataLeft = (float*)waveDataLeft;
    float* dataRight = (float*)waveDataRight;

    float left = 0;
    float right = 0;
    for(int a = 0; a < length; a++) {
        left = dataLeft[a];
        right = dataRight[a];

        if(convertNegativeToPositive) {
            if (left < 0) {
                left = -left;
            }
            if (right < 0) {
                right = -right;
            }
        }

        if (left < peakInfo->leftMin) {
            peakInfo->leftMin = left;
        }
        if (left > peakInfo->leftMax) {
            peakInfo->leftMax = left;
        }
        if (right < peakInfo->rightMin) {
            peakInfo->rightMin = right;
        }
        if (right > peakInfo->rightMax) {
            peakInfo->rightMax = right;
        }
        if (left < peakInfo->mixMin) {
            peakInfo->mixMin = left;
        }
        if (right < peakInfo->mixMin) {
            peakInfo->mixMin = right;
        }
        if (left > peakInfo->mixMax) {
            peakInfo->mixMax = left;
        }
        if (right > peakInfo->mixMax) {
            peakInfo->mixMax = right;
        }
    }
}
