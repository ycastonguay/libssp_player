//
//  ssp_eqpreset.h
//  sspPlayer
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef __player__ssp_eqpreset__
#define __player__ssp_eqpreset__

#include <stdio.h>
#include "ssp_structs.h"

SSP_EQPRESET* eqpreset_create();
void eqpreset_free(SSP_EQPRESET* preset);
void eqpreset_reset(SSP_EQPRESET* preset);
void eqpreset_normalize(SSP_EQPRESET* preset);

#endif /* defined(__player__ssp_eqpreset__) */
