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
#include <string.h>
#include "ssp_device.h"
#include "ssp_structs.h"

SSP_DEVICE* device_create() {
    SSP_DEVICE* device = malloc(sizeof(SSP_DEVICE));
    device_reset(device);
    return device;
}

void device_free(SSP_DEVICE *device) {
//    if(device->name != NULL) {
//        free(device->name);
//        //free((char *)device->name); // crashes on osx
//        //free((void *)device->name); // crashes on osx
//        //device->name = NULL;
//    }
}

void device_reset(SSP_DEVICE* device) {
    device->isInitialized = false;
    device->deviceId = -1;
    device->name = "Default device";
}

void device_copy(SSP_DEVICE* dest, SSP_DEVICE* src) {
    dest->deviceId = src->deviceId;
    dest->isInitialized = src->isInitialized;

    size_t len = strlen(src->name) + 1;
    dest->name = malloc(len);
    memcpy(dest->name, src->name, len);

    free(dest->name);
}