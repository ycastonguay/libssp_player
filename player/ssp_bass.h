//
//  ssp_bass.h
//  player
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef __player__ssp_bass__
#define __player__ssp_bass__

#include <stdio.h>
#import "ssp_errors.h"
#import "bass.h"

SSP_ERROR bass_init(DWORD device, DWORD sampleRate, DWORD bufferSize, DWORD updatePeriod, bool useFloatingPoint);

#endif /* defined(__player__ssp_bass__) */
