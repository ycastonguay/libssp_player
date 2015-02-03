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

#include <stdio.h>
#include <ncurses.h>
#include "ssp_public.h"

void checkForError(SSP_ERROR error) {
    if(error != SSP_OK) {
        printf("SSP Error code: %d\n", error);
    }
}

void logCallback(void *user, const char* str) {
    printf("libssp_player :: %s", str);
}

void stateChangedCallback(void *user, ssp_player_state_t state) {
    printf("Player state changed - state: %d\n", state);
}

void playlistIndexChangedCallback(void *user) {
    int currentIndex = SSP_Playlist_GetCurrentIndex();
    int count = SSP_Playlist_GetCount();
    SSP_PLAYLISTITEM* item = SSP_Playlist_GetItemAt(currentIndex);

    printf("Playlist index changed: [%d/%d]\n", currentIndex+1, count);
    printf("Playlist item file path: %s\n", item->audioFile->filePath);
}

void playlistEndedCallback(void *user) {
    printf("Playlist ended!");
}

int initializePlayer() {
    printf("Initializing player...\n");
    SSP_ERROR error = SSP_Init();
    if(error != SSP_OK) {
        checkForError(error);
        return 1;
    }

    SSP_SetLogCallback(logCallback, NULL);
    SSP_SetStateChangedCallback(stateChangedCallback, NULL);
    SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, NULL);
    SSP_SetPlaylistEndedCallback(playlistEndedCallback, NULL);

    error = SSP_InitDevice(-1, 44100, 1000, 100, true);
    if(error != SSP_OK) {
        checkForError(error);
        return 1;
    }

    SSP_DEVICE device2;
    SSP_GetDevice(&device2);

    printf("Adding items to playlist...\n");
    SSP_Playlist_AddItem("/Users/usr/Documents/mp3/1.mp3");
    SSP_Playlist_AddItem("/Users/usr/Documents/mp3/2.mp3");
    //SSP_Playlist_RemoveItemAt(0); // works and reorders the array, similar to a pop
    //SSP_Playlist_RemoveItemAt(1); // fails, vector.c vector_delete does not manage the last index of the list correctly... this does not reorder the array
    //SSP_Playlist_AddItem("hello3");

    printf("Starting playback...\n");
    error = SSP_Play();
    checkForError(error);

    printf("Player initialization successful!\n");
    return 0;
}

void destroyPlayer() {
    printf("Destroying player...\n");
    SSP_Stop();
    SSP_FreeDevice();
    SSP_Free();
    printf("Player destruction successful!\n");
}

int main(int argc, const char * argv[]) {
    int error = initializePlayer();
    if(error != 0) {
        return error;
    }

    printf("Press ENTER to stop playback...\n");
    int ch = getchar();

    destroyPlayer();

    //delay_output(0);
    //getch();

//    printf("--1\n");
//    initscr();			/* Start curses mode 		  */
//    printf("--2\n");
//    printw("Hello World !!!");	/* Print Hello World		  */
//    printf("--3\n");
//    refresh();			/* Print it on to the real screen */
//    printf("--4\n");
//    getch();			/* Wait for user input */
//    printf("--5\n");
//    endwin();			/* End curses mode		  */
//    printf("--6\n");

    printf("Finished execution with success!\n");
    
    return 0;
}
