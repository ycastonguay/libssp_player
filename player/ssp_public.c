//
//  ssp_public.c
//  player
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#include "ssp_public.h"
#include "ssp_privatestructs.h"

static SSP_PLAYER* sspPlayer; // static makes it private to this file

int SSP_GetBufferSize() {
    return 10;
}