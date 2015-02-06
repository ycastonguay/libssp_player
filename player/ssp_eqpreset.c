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

#include <stdlib.h>
#include <string.h>
#include "ssp_eqpreset.h"
#include "ssp_structs.h"

SSP_EQPRESET* eqpreset_create() {
    SSP_EQPRESET* preset = malloc(sizeof(SSP_EQPRESET));
    eqpreset_reset(preset);
    return preset;
}

void eqpreset_free(SSP_EQPRESET *preset) {
}

void eqpreset_copy(SSP_EQPRESET* dest, SSP_EQPRESET* src) {
    strncpy(dest->id, src->id, sizeof(src->id));
    strncpy(dest->name, src->name, sizeof(src->name));

    int numberOfBands = sizeof(src->bands) / sizeof(src->bands[0]);
    for (int a = 0; a < numberOfBands; a++) {
        dest->bands[a].bandwidth = src->bands[a].bandwidth;
        dest->bands[a].gain = src->bands[a].gain;
        dest->bands[a].q = src->bands[a].q;
        dest->bands[a].center = src->bands[a].center;
        strncpy(dest->bands[a].label, src->bands[a].label, sizeof(src->bands[a].label));
    }
}

void eqpreset_reset(SSP_EQPRESET* preset) {
    preset->id[0] = '\0';
    preset->name[0] = '\0';

    // Create bands
    int numberOfBands = sizeof(preset->bands) / sizeof(preset->bands[0]);
    for (int a = 0; a < numberOfBands; a++) {
        preset->bands[a].bandwidth = 0;
        preset->bands[a].gain = 0;
        preset->bands[a].q = 1;
        preset->bands[a].center = 0;
        preset->bands[a].label[0] = '\0';
    }

    // Set default centers
    preset->bands[0].center = 55;
    strcpy(preset->bands[0].label, "55 Hz\0");
    preset->bands[1].center = 77;
    strcpy(preset->bands[1].label, "77 Hz\0");
    preset->bands[2].center = 110;
    strcpy(preset->bands[2].label, "110 Hz\0");
    preset->bands[3].center = 156;
    strcpy(preset->bands[3].label, "156 Hz\0");
    preset->bands[4].center = 220;
    strcpy(preset->bands[4].label, "220 Hz\0");
    preset->bands[5].center = 311;
    strcpy(preset->bands[5].label, "311 Hz\0");
    preset->bands[6].center = 440;
    strcpy(preset->bands[6].label, "440 Hz\0");
    preset->bands[7].center = 622;
    strcpy(preset->bands[7].label, "622 Hz\0");
    preset->bands[8].center = 880;
    strcpy(preset->bands[8].label, "880 Hz\0");
    preset->bands[9].center = 1200;
    strcpy(preset->bands[9].label, "1.2 kHz\0");
    preset->bands[10].center = 1800;
    strcpy(preset->bands[10].label, "1.8 kHz\0");
    preset->bands[11].center = 2500;
    strcpy(preset->bands[11].label, "2.5 kHz\0");
    preset->bands[12].center = 3500;
    strcpy(preset->bands[12].label, "3.5 kHz\0");
    preset->bands[13].center = 5000;
    strcpy(preset->bands[13].label, "5 kHz\0");
    preset->bands[14].center = 7000;
    strcpy(preset->bands[14].label, "7 kHz\0");
    preset->bands[15].center = 10000;
    strcpy(preset->bands[15].label, "10 kHz\0");
    preset->bands[16].center = 14000;
    strcpy(preset->bands[16].label, "14 kHz\0");
    preset->bands[17].center = 20000;
    strcpy(preset->bands[17].label, "20 kHz\0");
};

void eqpreset_normalize(SSP_EQPRESET* preset) {
    float highestValue = -6;
    float value = 0;

    // Try to find the highest value in all bands
    int numberOfBands = sizeof(preset->bands) / sizeof(preset->bands[0]);
    for (int a = 0; a < numberOfBands; a++) {
        value = preset->bands[a].gain;
        if (value > highestValue)
            highestValue = value;
    }

    // Normalize bands
    for (int b = 0; b < numberOfBands; b++) {
        preset->bands[b].gain = preset->bands[b].gain - highestValue;
    }
}
