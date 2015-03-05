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
#include "../bass/bass.h"
#include "ssp_device.h"
#include "ssp_util.h"

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
    device->isDefault = false;
    device->deviceId = -1;
    device->name = "Default device";
    device->driver = NULL;
}

void device_copy(SSP_DEVICE* dest, SSP_DEVICE* src) {
    dest->deviceId = src->deviceId;
    dest->isDefault = src->isDefault;
    dest->isInitialized = src->isInitialized;
    dest->name = copystr((char *)dest->name, src->name);
    dest->driver = copystr((char *)dest->driver, src->driver);
}

int device_getOutputDeviceCount() {
    int a = 0;
    int count = 0;
    BASS_DEVICEINFO info;
    for (a=0; BASS_GetDeviceInfo(a, &info); a++) {
        if (info.flags & BASS_DEVICE_ENABLED) {
            count++;
        }
    }
    return count;
}

bool device_getOutputDevice(int index, SSP_DEVICE *device) {
    int a = 0;
    int count = 0;
    BASS_DEVICEINFO info;
    for (a=0; BASS_GetDeviceInfo(a, &info); a++) {
        if (info.flags & BASS_DEVICE_ENABLED) {
            count++;

            if(index == count - 1) {
                device->deviceId = a;
                device->isDefault = (bool) (info.flags & BASS_DEVICE_DEFAULT);

                device->name = copystr((char *) device->name, info.name);
                device->driver = copystr((char *) device->driver, info.driver);

//            if (device.Name.ToUpper() != "NO SOUND")
//                devices.Add(device);

                return true;
            }
        }
    }

    return false;
}
