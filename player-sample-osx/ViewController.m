//
//  ViewController.m
//  player-sample-osx
//
//  Created by Yanick Castonguay on 2015-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#import "ViewController.h"
#import "ssp_public.h"

@interface ViewController () {
    NSTimer *timer;
}
@end

@implementation ViewController

//static void testCallback() {
void playlistIndexChangedCallback(void *user) {
    printf("Test callback\n");
    int currentIndex = SSP_Playlist_GetCurrentIndex();
    int count = SSP_Playlist_GetCount();
    NSLog(@"playlistIndexChangedCallback - index: %d / count: %d", currentIndex, count);
    //[_lblPosition stringValue] = @"";
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initializePlayer];
}

- (void)initializePlayer {
    SSP_ERROR error = SSP_Init();
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }
    
    error = SSP_InitDevice(-1, 44100, 1000, 100, true);
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }

    SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, NULL); //(void *)self);
    
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
    
    SSP_Play();
}

- (IBAction)actionClose:(id)sender {
    SSP_Free();
    [NSApp terminate:self];
}

@end
