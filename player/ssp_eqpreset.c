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
    return preset;
}

void eqpreset_free(SSP_EQPRESET *preset) {
    if(preset->name) {
        free(preset->name);
        preset->name = NULL;
    }
}

SSP_EQPRESET* eqpreset_copy(SSP_EQPRESET* preset) {
    SSP_EQPRESET* newpreset = malloc(sizeof(SSP_EQPRESET));
    memcpy(newpreset, preset, sizeof(SSP_EQPRESET));
    return newpreset;
}

void eqpreset_reset(SSP_EQPRESET* preset) {

}

void eqpreset_normalize(SSP_EQPRESET* preset) {

}
