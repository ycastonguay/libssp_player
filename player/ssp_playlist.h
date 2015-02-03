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

#ifndef player_ssp_playlist____FILEEXTENSION___
#define player_ssp_playlist____FILEEXTENSION___

#include "ssp_structs.h"
#include "ssp_errors.h"
#include "ssp_privatestructs.h"

SSP_PLAYLIST* playlist_create();
void playlist_free(SSP_PLAYLIST *playlist);
SSP_ERROR playlist_disposeChannels(SSP_PLAYLIST *playlist);

SSP_ERROR playlist_addItem(SSP_PLAYLIST *playlist, char *filePath);
SSP_ERROR playlist_insertItemAt(SSP_PLAYLIST *playlist, char* filePath, int index);
SSP_ERROR playlist_removeItemAt(SSP_PLAYLIST *playlist, int index);
SSP_ERROR playlist_clear(SSP_PLAYLIST *playlist);
SSP_PLAYLISTITEM* playlist_getItemAt(SSP_PLAYLIST *playlist, int index);
SSP_PLAYLISTITEM* playlist_getCurrentItem(SSP_PLAYLIST *playlist);
SSP_PLAYLISTITEM* playlist_getCurrentMixerItem(SSP_PLAYLIST *playlist);
int playlist_getCount(SSP_PLAYLIST *playlist);

// TODO: Split into ssp_playlistitem.h
SSP_PLAYLISTITEM* playlistitem_create();
void playlistitem_free(SSP_PLAYLISTITEM *item);
void playlistitem_reset(SSP_PLAYLISTITEM *item);
void playlistitem_copy(SSP_PLAYLISTITEM *itemSrc, SSP_PLAYLISTITEM *itemDest);
void playlistitem_load(SSP_PLAYLISTITEM *item, bool useFloatingPoint);
SSP_ERROR playlistitem_disposeChannel(SSP_PLAYLISTITEM *item);

#endif
