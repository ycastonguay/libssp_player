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
    NSTimer *timer;
}
@end

@implementation ViewController

void logCallback(void *user, const char* str) {
    printf("libssp_player :: %s", str);
}

void playlistIndexChangedCallback(void *user) {
    ViewController* refObj = (__bridge_transfer id) user;

    int currentIndex = SSP_Playlist_GetCurrentIndex();
    int count = SSP_Playlist_GetCount();
    SSP_PLAYLISTITEM* item = SSP_Playlist_GetItemAt(currentIndex);

    refObj.lblPlaylist.stringValue = [NSString stringWithFormat:@"Playlist [%d/%d]", currentIndex+1, count];
    refObj.lblFilePath.stringValue = [NSString stringWithFormat:@"File path: %s", item->audioFile->filePath];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initializePlayer];
}

- (void)initializePlayer {

    // Get version
    int version = SSP_GetVersion();
    NSLog(@"libssp_player version: %d", version);

    // Set callback for logging
    SSP_SetLogCallback(logCallback, NULL);

    // Init player
    SSP_ERROR error = SSP_Init();
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }

    // Init device
    error = SSP_InitDevice(-1, 44100, 1000, 100, true);
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }

    // Set player callbacks
    void* test = (__bridge_retained void *)self;
    SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, test);

    // Setup timer for refreshing position
    timer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(timerElapsed) userInfo:nil repeats:YES];
}

- (void)timerElapsed {
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
