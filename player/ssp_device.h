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

#ifndef __player__ssp_device__
#define __player__ssp_device__

#include <stdio.h>
#include "ssp_structs.h"
#include "ssp_errors.h"

SSP_DEVICE* device_create();
void device_free(SSP_DEVICE *device);
void device_reset(SSP_DEVICE *device);
void device_copy(SSP_DEVICE *dest, SSP_DEVICE *src);

int device_getOutputDeviceCount();
bool device_getOutputDevice(int index, SSP_DEVICE *device);

#endif /* defined(__player__ssp_device__) */
