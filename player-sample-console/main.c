//
//  main.c
//  sspPlayer
//
//  Created by Yanick Castonguay on 2015-01-19.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#include <stdio.h>
#include "ssp_player.h"

int main(int argc, const char * argv[]) {
    
    SSP_MIXER mixerProperties;
    mixerProperties.sampleRate = 44100;
    mixerProperties.bufferSize = 1000;
    mixerProperties.updatePeriod = 100;
    
    // Initialize sspPlayer
    printf("Initializing sspPlayer...\n");
    int error = SSP_Init(-1, 44100, 1000, 100, true);
    if(error != SSP_ERROR_OK) {
        printf("Player initialization failed!\n");
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

    SSP_Play();

    printf("Finished execution with success.\n");
    
    return 0;
}
