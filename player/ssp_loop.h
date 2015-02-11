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

#ifndef __player__ssp_loop__
#define __player__ssp_loop__

#include <stdio.h>
#include "ssp_structs.h"
#include "ssp_errors.h"

SSP_LOOP* loop_create();
void loop_free(SSP_LOOP *loop);
void loop_reset(SSP_LOOP *loop);
void loop_copy(SSP_LOOP *dest, SSP_LOOP *src);
SSP_ERROR loop_validate(SSP_LOOP* loop);

#endif /* defined(__player__ssp_loop__) */
