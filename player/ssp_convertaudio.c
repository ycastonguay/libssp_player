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
#include "ssp_convertaudio.h"

__uint64_t convertAudio_toSamples(__uint64_t milliseconds, int sampleRate) {
    return milliseconds * (sampleRate / 1000);
}

__uint64_t convertAudio_toSamplesFromBytes(__uint64_t bytes, int bitsPerSample, int channelCount) {
    return bytes * 8 / bitsPerSample / channelCount;
}

__uint64_t convertAudio_toMS(__uint64_t samples, int sampleRate) {
    return samples * 1000 / sampleRate;
}

__uint64_t convertAudio_toBytes(__uint64_t samples, int bitRate, int channelCount) {
    return samples * bitRate * channelCount / 8;
}

float convertAudio_msToTempo(float milliseconds) {
    return (60.0f / milliseconds) * 1000;
}

float convertAudio_tempoToMS(float tempo) {
    return 60000.0f / tempo;
}

float convertAudio_levelToDB(float level, float maxLevel) {
    return 20.0f * log10f(level / maxLevel);
}

char* convertAudio_toStringFromMS(__uint64_t milliseconds) {
    __uint64_t pos = milliseconds;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    __uint64_t ms = 0;
    char* timeString = "";

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
    ms = pos;

    if(hours > 0) {
        sprintf(timeString, "%01d:%02d:%02d.%03d", hours, minutes, seconds, ms);
    }
    else {
        sprintf(timeString, "%02d:%02d.%03d", minutes, seconds, ms);
    }

    return timeString;
}

//
///// <summary>
///// Converts to the milliseconds format.
///// </summary>
///// <param name="position">Position in string (format: 0:00.000)</param>
///// <returns>Milliseconds</returns>
//public static int ToMS(string position)
//{
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
//}

__uint64_t convertAudio_toMSFromString(const char* string) {
    return 0;
}

char* convertAudio_toString(__uint64_t bytes, int bitsPerSample, int channelCount, int sampleRate) {
    __uint64_t samples = convertAudio_toSamplesFromBytes(bytes, bitsPerSample, channelCount);
    __uint64_t milliseconds = convertAudio_toMS(samples, sampleRate);
//    return ToTimeString(positionMS);
    return NULL;
}

