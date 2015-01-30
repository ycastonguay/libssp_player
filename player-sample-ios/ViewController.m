//
//  ViewController.m
//  player-sample-ios
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
//    self.lblPosition.stringValue = [NSString stringWithFormat:@"Position (bytes): %lld", position];
}

- (IBAction)actionOpenAudioFiles:(id)sender {
}

- (IBAction)actionClose:(id)sender {
}
@end
