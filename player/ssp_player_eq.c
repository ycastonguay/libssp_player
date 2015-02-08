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

#include <string.h>
#include <stdlib.h>
#include "../bass/bassmix.h"
#include "../bass/bass_fx.h"
#include "ssp_player.h"
#include "ssp_eqpreset.h"
#include "ssp_bass.h"
#include "ssp_privatestructs.h"

SSP_ERROR player_createEQStage(SSP_PLAYER* player) {
    if(player->handles->eqFX != 0) {
        return SSP_ERROR_EQ_STAGE_ALREADYEXISTS;
    }

    player->handles->eqFX = BASS_ChannelSetFX(player->handles->mixerChannel, BASS_FX_BFX_PEAKEQ, 0);
    if(player->handles->eqFX == 0) {
        bass_getError("player_createEQStage");
        return SSP_ERROR_EQ_STAGE_FAILEDTOCREATE;
    }
    return SSP_OK;
}

SSP_ERROR player_removeEQStage(SSP_PLAYER* player) {
    if(player->handles->eqFX == 0) {
        return SSP_ERROR_EQ_STAGE_DOESNOTEXIST;
    }

    bool success = BASS_ChannelRemoveFX(player->handles->mixerChannel, player->handles->eqFX);
    if(!success) {
        bass_getError("player_removeEQStage");
        return SSP_ERROR_EQ_STAGE_FAILEDTOREMOVE;
    }

    player->handles->eqFX = 0;
    return SSP_OK;
}

SSP_ERROR player_updateEQBand(SSP_PLAYER* player, int band, float gain) {
    if(player->handles->eqFX == 0) {
        return SSP_ERROR_EQ_STAGE_DOESNOTEXIST;
    }

    //player->eqPreset->bands[band].gain = gain;

    // remove bpm callbacks

    BASS_BFX_PEAKEQ eq;
    eq.lBand = band;
    bool success = BASS_FXGetParameters(player->handles->eqFX, &eq);
    if(!success) {
        return bass_getError("player_updateEQBand");
    }

    eq.fGain = gain;
    success = BASS_FXSetParameters(player->handles->eqFX, &eq);
    if(!success) {
        return bass_getError("player_updateEQBand");
    }

    // add bpm callbacks

    return SSP_OK;
}

SSP_ERROR player_applyEQ(SSP_PLAYER* player, SSP_EQPRESET* eqpreset) {
    eqpreset_copy(player->eqPreset, eqpreset);
    // remove bpm callback

    int numberOfBands = sizeof(player->eqPreset->bands)/sizeof(player->eqPreset->bands[0]);
    for(int a = 0; a < numberOfBands; a++) {
        BASS_BFX_PEAKEQ eq;
        eq.lBand = a;
        eq.lChannel = BASS_BFX_CHANALL;
        eq.fCenter = eqpreset->bands[a].center;
        eq.fGain = eqpreset->bands[a].gain;
        eq.fQ = eqpreset->bands[a].q;

        bool success = BASS_FXSetParameters(player->handles->eqFX, &eq);
        if(!success) {
            return bass_getError("player_applyEQ");
        }
    }

    // add bpm callback
    return SSP_OK;
}

SSP_ERROR player_resetEQ(SSP_PLAYER* player) {
    SSP_ERROR error;
    int numberOfBands = sizeof(player->eqPreset->bands)/sizeof(player->eqPreset->bands[0]);
    for(int a = 0; a < numberOfBands; a++) {
        player->eqPreset->bands[a].gain = 0;
        error = player_updateEQBand(player, a, 0);
        if(error != SSP_OK) {
            return error;
        }
    }

    return SSP_OK;
}

SSP_ERROR player_enableEQ(SSP_PLAYER* player, bool enabled) {
    SSP_ERROR error;

    player->playhead->isEQEnabled = enabled;
    if(enabled) {
        error = player_applyEQ(player, player->eqPreset);
    }
    else {
        error = player_resetEQ(player);
    }

    return error;
}

SSP_ERROR player_normalizeEQ(SSP_PLAYER* player) {
    eqpreset_normalize(player->eqPreset);
    return player_applyEQ(player, player->eqPreset);
}
