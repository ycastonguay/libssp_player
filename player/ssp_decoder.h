#include "ssp_errors.h"// Copyright © 2011-2015 Yanick Castonguay
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

#ifndef __player__ssp_decoder__
#define __player__ssp_decoder__

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "ssp_errors.h"

uint32_t decoder_createStream(char* filePath, bool useFloatingPoint);
SSP_ERROR decoder_freeStream(uint32_t handle);
uint64_t decoder_getLength(uint32_t handle);
uint64_t decoder_getData(uint32_t handle, void* buffer, int length);

#endif /* defined(__player__ssp_decoder__) */
