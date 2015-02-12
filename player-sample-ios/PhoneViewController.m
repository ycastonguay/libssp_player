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

#import "PhoneViewController.h"
#import "ssp_public.h"

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
    SSP_PLAYLISTITEM item;
    SSP_Playlist_GetItemAt(currentIndex, &item);
    runOnMainQueueWithoutDeadlocking(^{
        mainViewController.lblPlaylist.text = [NSString stringWithFormat:@"Playlist [%d/%d]", currentIndex+1, count];
        mainViewController.lblFilePath.text = [NSString stringWithFormat:@"File path: %s", item.filePath];
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

    SSP_ERROR error = SSP_Init(NULL);
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
    SSP_POSITION pos;
    SSP_GetPosition(&pos);
    self.lblPosition.text = [NSString stringWithFormat:@"Position: %s", pos.str];
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
