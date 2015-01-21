//
//  ssp_playhead.h
//  sspPlayer
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef __player__ssp_playhead__
#define __player__ssp_playhead__

#include <stdio.h>
#include "ssp_structs.h"

SSP_PLAYHEAD* playhead_create();
void playhead_free(SSP_PLAYHEAD *playhead);
void playhead_reset(SSP_PLAYHEAD* playhead);

#endif /* defined(__player__ssp_playhead__) */
