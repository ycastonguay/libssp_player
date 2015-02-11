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
#include "ssp_loop.h"
#include "ssp_structs.h"
#include "ssp_errors.h"

SSP_LOOP* loop_create() {
    SSP_LOOP* loop = malloc(sizeof(SSP_LOOP));
    loop_reset(loop);
    return loop;
}

void loop_free(SSP_LOOP *loop) {
}

void loop_reset(SSP_LOOP* loop) {
    loop->startPosition = 0;
    loop->endPosition = 0;
}

void loop_copy(SSP_LOOP *dest, SSP_LOOP *src) {
    dest->startPosition = src->startPosition;
    dest->endPosition = src->endPosition;
}

SSP_ERROR loop_validate(SSP_LOOP* loop) {
    if(loop == NULL) {
        return SSP_ERROR_LOOP_INVALID;
    }

    if(loop->endPosition <= loop->startPosition) {
        return SSP_ERROR_LOOP_INVALID;
    }

    return SSP_OK;
}