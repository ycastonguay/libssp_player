//
//  sspPlayer.h
//  sspPlayer
//
//  Created by Yanick Castonguay on 2015-01-19.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef player_ssp_player____FILEEXTENSION___
#define player_ssp_player____FILEEXTENSION___

#include <stdbool.h>
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_callbacks.h"
#include "ssp_privatestructs.h"

SSP_PLAYER* player_create();
void player_free(SSP_PLAYER* sspPlayer);

SSP_ERROR player_init(SSP_PLAYER* player, int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);

SSP_ERROR player_pause(SSP_PLAYER* player);
SSP_ERROR player_stop(SSP_PLAYER* player);
SSP_ERROR player_play(SSP_PLAYER* player);
SSP_ERROR player_previous(SSP_PLAYER* player);
SSP_ERROR player_next(SSP_PLAYER* player);
SSP_ERROR player_goTo(SSP_PLAYER* player, int index);

#endif
