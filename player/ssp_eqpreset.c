//
//  ssp_eqpreset.c
//  sspPlayer
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

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
