//
//  PhoneViewController.m
//  player-sample-ios
//
//  Created by Yanick Castonguay on 2015-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#import "PhoneViewController.h"
#import "ssp_public.h"
#import "ssp_structs.h"

// Evil way to make the view controller available to C callback methods, not trying to do anything fancy here
static PhoneViewController* mainViewController = nil;

@interface PhoneViewController () {
    NSTimer *timerRefreshPosition;
}
@end

@implementation PhoneViewController

void runOnMainQueueWithoutDeadlocking(void (^block)(void))
{
    if ([NSThread isMainThread])
    {
        block();
    }
    else
    {
        dispatch_sync(dispatch_get_main_queue(), block);
    }
}

void logCallback(void *user, const char* str) {
    printf("libssp_player :: %s", str);
}

void playlistIndexChangedCallback(void *user) {
    //PhoneViewController* vc = (__bridge_transfer id) user; // this crashes the app eventually
    int currentIndex = SSP_Playlist_GetCurrentIndex();
    int count = SSP_Playlist_GetCount();
    SSP_PLAYLISTITEM* item = SSP_Playlist_GetItemAt(currentIndex);
    //SSP_PLAYLISTITEM item;
    //SSP_Playlist_GetItemAtNew(currentIndex, &item);
    runOnMainQueueWithoutDeadlocking(^{
        mainViewController.lblPlaylist.text = [NSString stringWithFormat:@"Playlist [%d/%d]", currentIndex+1, count];
        mainViewController.lblFilePath.text = [NSString stringWithFormat:@"File path: %s", item->filePath];
    });
}

void playlistEndedCallback(void *user) {
    runOnMainQueueWithoutDeadlocking(^{
        mainViewController.lblPlaylist.text = [NSString stringWithFormat:@"Playlist ended"];
    });
}

void stateChangedCallback(void *user, ssp_player_state_t state) {
    runOnMainQueueWithoutDeadlocking(^{
        mainViewController.lblState.text = [NSString stringWithFormat:@"Player state: %d", state];
    });
}

- (void)viewDidLoad {
    [super viewDidLoad];
    mainViewController = self;
    [self initializePlayer];
    [self buildPlaylist];
}

- (void)initializePlayer {
    int version = SSP_GetVersion();
    NSLog(@"libssp_player version: %d", version);
    _lblVersion.text = [NSString stringWithFormat:@"Version %d", version];

    SSP_ERROR error = SSP_Init();
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }

    SSP_SetLogCallback(logCallback, NULL);
    //SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, (__bridge_retained void *)self); // eventually crashes the app
    SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, NULL);
    SSP_SetPlaylistEndedCallback(playlistEndedCallback, NULL);
    SSP_SetStateChangedCallback(stateChangedCallback, NULL);

    error = SSP_InitDevice(-1, 44100, 1000, 100, true);
    if(error != SSP_OK) {
        NSLog(@"Error!");
        return;
    }

    timerRefreshPosition = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(timerRefreshPositionElapsed) userInfo:nil repeats:YES];
}

- (void)buildPlaylist {
    SSP_Playlist_Clear();
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSArray *array = [[NSFileManager defaultManager] subpathsOfDirectoryAtPath:documentsDirectory error:nil];
    for(NSString *filePath in array) {
        NSString *filePathWithDirectory = [NSString stringWithFormat:@"%@/%@", documentsDirectory, filePath];
        NSLog(@"filePath: %@", filePathWithDirectory);
        const char* str = [filePathWithDirectory UTF8String];
        SSP_Playlist_AddItem(str);
    }
}

- (void)timerRefreshPositionElapsed {
    uint64_t position = SSP_GetPosition();

    // Can't find the right way to do this in Obj-C
    SSP_POSITION pos;
    SSP_GetPositionNew(&pos);
    //SSP_POSITION* pos = malloc(sizeof(SSP_POSITION));
    //SSP_GetPositionNew(pos);

    //self.lblPosition.text = [NSString stringWithFormat:@"Position (bytes): %lld", position];
    self.lblPosition.text = [NSString stringWithFormat:@"Position (bytes): %lld", pos.bytes];
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
