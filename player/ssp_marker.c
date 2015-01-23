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
#include "ssp_marker.h"
#include "ssp_structs.h"

SSP_MARKER* marker_create() {
    SSP_MARKER* marker = malloc(sizeof(SSP_MARKER));
    marker_reset(marker);
    return marker;
}

void marker_free(SSP_MARKER *marker) {
    if(marker->name != NULL) {
        free(marker->name);
        marker->name = NULL;
    }
}

void marker_reset(SSP_MARKER* marker) {
    marker->name = "New marker";
    marker->position = 0;
}