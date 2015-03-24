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

#ifndef __player__ssp_playlistitem__
#define __player__ssp_playlistitem__

#include "ssp_structs.h"
#include "ssp_errors.h"
#include "ssp_privatestructs.h"

SSP_PLAYLISTITEM* playlistitem_create();
void playlistitem_free(SSP_PLAYLISTITEM *item);
void playlistitem_reset(SSP_PLAYLISTITEM *item);
void playlistitem_copy(SSP_PLAYLISTITEM *itemSrc, SSP_PLAYLISTITEM *itemDest);
SSP_ERROR playlistitem_load(SSP_PLAYLISTITEM *item, bool useFloatingPoint);

#endif /* defined(__player__ssp_playlistitem__) */
