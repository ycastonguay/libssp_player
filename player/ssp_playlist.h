//
//  ssp_playlist.h
//  sspPlayer
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef player_ssp_playlist____FILEEXTENSION___
#define player_ssp_playlist____FILEEXTENSION___

#import "ssp_structs.h"
#import "ssp_errors.h"
#import "ssp_privatestructs.h"

SSP_PLAYLIST* playlist_create();
void playlist_free(SSP_PLAYLIST *playlist);
int playlist_addItem(SSP_PLAYLIST *playlist, char *filePath);
int playlist_insertItemAt(SSP_PLAYLIST *playlist, char* filePath, int index);
int playlist_removeItemAt(SSP_PLAYLIST *playlist, int index);
int playlist_removeItems(SSP_PLAYLIST *playlist);
SSP_PLAYLISTITEM* playlist_getItemAt(SSP_PLAYLIST *playlist, int index);
int playlist_getCount(SSP_PLAYLIST *playlist);

SSP_PLAYLISTITEM* playlistitem_create();
void playlistitem_free(SSP_PLAYLISTITEM *item);

#endif
