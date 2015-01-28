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

#include <string.h>
#include <stdlib.h>
#include "ssp_public.h"
#include "ssp_privatestructs.h"
#include "ssp_errors.h"
#include "ssp_playlist.h"
#include "ssp_player.h"
#include "ssp_structs.h"

static SSP_PLAYER* sspPlayer;

#pragma mark Initialization

int SSP_GetVersion() {
    return SSP_VERSION;
}

SSP_ERROR SSP_Init() {
    // Create player if not created yet
    if(sspPlayer == NULL) {
        sspPlayer = player_create();
    }

    return player_init(sspPlayer);
}

SSP_ERROR SSP_InitDevice(int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    return player_initDevice(sspPlayer, deviceId, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
}

SSP_ERROR SSP_FreeDevice() {
    return player_freeDevice(sspPlayer);
}

#pragma mark Callbacks

void SSP_SetPlaylistIndexChangedCallback(player_playlistindexchanged_cb cb, void *user) {
    player_setPlaylistIndexChangedCallback(sspPlayer, cb, user);
}

void SSP_RemovePlaylistIndexChangedCallback() {
    player_removePlaylistIndexChangedCallback(sspPlayer);
}

#pragma mark Device

void SSP_GetDevice(SSP_DEVICE* device) {

    // TODO: Find a better way to copy structs w/ strings, memcpy?
    SSP_DEVICE *deviceToCopy = sspPlayer->device;
    device->deviceId = deviceToCopy->deviceId;
    device->isInitialized = deviceToCopy->isInitialized;
    //device->name = malloc(sizeof(deviceToCopy->name)); // works in c, crashes in c# and vice versa!

    strcpy(device->name, deviceToCopy->name);
    device->test = 15000;

    // Can't get this to work in C#...
    //memcpy(device, sspPlayer->device, sizeof(SSP_DEVICE));
    printf("---> getDevice - name: %s\n", sspPlayer->device->name);
}

#pragma mark Playback

SSP_ERROR SSP_Play() {
    return player_play(sspPlayer);
}

SSP_ERROR SSP_Pause() {
    return player_pause(sspPlayer);
}

SSP_ERROR SSP_Stop() {
    return player_stop(sspPlayer);
}

SSP_ERROR SSP_Previous() {
    return player_previous(sspPlayer);
}

SSP_ERROR SSP_Next() {
    return player_next(sspPlayer);
}

SSP_ERROR SSP_GoTo(int index) {
    return player_goTo(sspPlayer, index);
}

#pragma mark Playlist

int SSP_Playlist_AddItem(char* filePath) {
    return playlist_addItem(sspPlayer->playlist, filePath);
}

int SSP_Playlist_InsertItemAt(char* filePath, int index) {
    return playlist_insertItemAt(sspPlayer->playlist, filePath, index);
}

int SSP_Playlist_RemoveItemAt(int index) {
    return playlist_removeItemAt(sspPlayer->playlist, index);
}

int SSP_Playlist_Clear() {
    return playlist_clear(sspPlayer->playlist);
}

SSP_PLAYLISTITEM* SSP_Playlist_GetItemAt(int index) {
    return playlist_getItemAt(sspPlayer->playlist, index);
}

int SSP_Playlist_GetCount() {
    return playlist_getCount(sspPlayer->playlist);
}

int SSP_Playlist_GetCurrentIndex() {
    return sspPlayer->playlist->currentIndex;
}

#pragma mark EQ Presets

SSP_EQPRESET* SSP_GetEQPreset() {
    SSP_EQPRESET* preset = malloc(sizeof(SSP_EQPRESET));
    memcpy(preset, sspPlayer->eqPreset, sizeof(SSP_EQPRESET));
    return preset;
}

#pragma mark Seek / Position

uint64_t SSP_GetPosition() {
    return player_getPosition(sspPlayer);
}

SSP_ERROR SSP_SetPosition(uint64_t position) {
    return player_setPosition(sspPlayer, position);
}