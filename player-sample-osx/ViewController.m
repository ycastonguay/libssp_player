//
//  ViewController.m
//  player-sample-osx
//
//  Created by Yanick Castonguay on 2015-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#import "ViewController.h"
#import "ssp_public.h"
#import "ssp_structs.h"

@interface ViewController () {
    NSTimer *timerRefreshPosition;
}
@end

@implementation ViewController

void logCallback(void *user, const char* str) {
    printf("libssp_player :: %s", str);
}

void playlistIndexChangedCallback(void *user) {
    ViewController* vc = (__bridge_transfer id) user;

    int currentIndex = SSP_Playlist_GetCurrentIndex();
    int count = SSP_Playlist_GetCount();
    SSP_PLAYLISTITEM* item = SSP_Playlist_GetItemAt(currentIndex);

    vc.lblPlaylist.stringValue = [NSString stringWithFormat:@"Playlist [%d/%d]", currentIndex+1, count];
    vc.lblFilePath.stringValue = [NSString stringWithFormat:@"File path: %s", item->audioFile->filePath];
}

void playlistEndedCallback(void *user) {
    ViewController* vc = (__bridge_transfer id) user;
    vc.lblPlaylist.stringValue = [NSString stringWithFormat:@"Playlist ended"];
}

void stateChangedCallback(void *user, ssp_player_state_t state) {
    ViewController* vc = (__bridge_transfer id) user;
    vc.lblState.stringValue = [NSString stringWithFormat:@"Player state: %d", state];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initializePlayer];
}

- (void)initializePlayer {
    int version = SSP_GetVersion();
    NSLog(@"libssp_player version: %d", version);

    SSP_ERROR error = SSP_Init();
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }
    
    SSP_SetLogCallback(logCallback, NULL);
    SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, (__bridge_retained void *)self);
    SSP_SetPlaylistEndedCallback(playlistEndedCallback, (__bridge_retained void *)self);
    SSP_SetStateChangedCallback(stateChangedCallback, (__bridge_retained void *)self);

    error = SSP_InitDevice(-1, 44100, 1000, 100, true);
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }

    timerRefreshPosition = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(timerRefreshPositionElapsed) userInfo:nil repeats:YES];
}

- (void)timerRefreshPositionElapsed {
    uint64_t position = SSP_GetPosition();
    self.lblPosition.stringValue = [NSString stringWithFormat:@"Position (bytes): %lld", position];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)actionOpenAudioFiles:(id)sender {
    NSArray *fileTypes = [NSArray arrayWithObjects:@"mp3", @"wav", @"flac", nil];
    NSOpenPanel *panel = [NSOpenPanel openPanel];
    panel.allowsMultipleSelection = YES;
    panel.canChooseDirectories = NO;
    panel.canChooseFiles = YES;
    panel.floatingPanel = YES;
    panel.allowedFileTypes = fileTypes;
    
    SSP_Playlist_Clear();

    if([panel runModal] == NSOKButton) {
        for(int a = 0; a < panel.URLs.count; a++) {
            NSURL *url = [panel.URLs objectAtIndex:a];
            const char* hello = [url.path UTF8String];
            SSP_Playlist_AddItem(hello);
        }
    }
    
    //SSP_Play();
}

- (IBAction)actionClose:(id)sender {
    SSP_Free();
    [NSApp terminate:self];
}

- (IBAction)actionPlay:(id)sender {
    SSP_ERROR error = SSP_Play();
    if(error != SSP_OK) {
        NSLog(@"libssp_player error: %d", error);
    }
}

- (IBAction)actionPause:(id)sender {
    SSP_ERROR error = SSP_Pause();
    if(error != SSP_OK) {
        NSLog(@"libssp_player error: %d", error);
    }
}

- (IBAction)actionStop:(id)sender {
    SSP_ERROR error = SSP_Stop();
    if(error != SSP_OK) {
        NSLog(@"libssp_player error: %d", error);
    }
}

- (IBAction)actionPrevious:(id)sender {
    SSP_ERROR error = SSP_Previous();
    if(error != SSP_OK) {
        NSLog(@"libssp_player error: %d", error);
    }
}

- (IBAction)actionNext:(id)sender {
    SSP_ERROR error = SSP_Next();
    if(error != SSP_OK) {
        NSLog(@"libssp_player error: %d", error);
    }
}

@end
