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

#ifndef __player__ssp_playhead__
#define __player__ssp_playhead__

#include <stdio.h>
#include "ssp_privatestructs.h"

SSP_PLAYHEAD* playhead_create();
void playhead_free(SSP_PLAYHEAD *playhead);
void playhead_reset(SSP_PLAYHEAD* playhead);

#endif /* defined(__player__ssp_playhead__) */
