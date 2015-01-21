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
#include "ssp_public.h"

void checkForError(SSP_ERROR error) {
    if(error != SSP_ERROR_OK) {
        printf("SSP Error code: %d\n", error);
    }
}

int main(int argc, const char * argv[]) {
    
    // Initialize player
    printf("Initializing player...\n");
    SSP_ERROR error = SSP_Init(-1, 44100, 1000, 100, true);
    if(error != SSP_ERROR_OK) {
        checkForError(error);
        return 1;
    }
    else {
        printf("Player initialization successful!\n");
    }

    printf("Adding items to playlist...\n");
    SSP_Playlist_AddItem("hello");
    SSP_Playlist_AddItem("hello2");
    SSP_Playlist_RemoveItemAt(0); // works and reorders the array, similar to a pop
    //SSP_Playlist_RemoveItemAt(1); // fails, vector.c vector_delete does not manage the last index of the list correctly... this does not reorder the array
    SSP_Playlist_AddItem("hello3");

    printf("Starting playback...\n");
    error = SSP_Play();
    checkForError(error);

    printf("Finished execution with success!\n");
    
    return 0;
}
