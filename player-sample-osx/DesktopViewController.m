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

#import "DesktopViewController.h"
#import "ssp_public.h"
#import "ssp_structs.h"

// Evil way to make the view controller available to C callback methods, not trying to do anything fancy here
static DesktopViewController* mainViewController = nil;

@interface DesktopViewController () {
    NSTimer *timerRefreshPosition;
}
@end

@implementation DesktopViewController

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
        mainViewController.lblPlaylist.stringValue = [NSString stringWithFormat:@"Playlist [%d/%d]", currentIndex+1, count];
        mainViewController.lblFilePath.stringValue = [NSString stringWithFormat:@"File path: %s", item.filePath];
    });
}

void playlistEndedCallback(void *user) {
    runOnMainQueueWithoutDeadlocking(^{
        mainViewController.lblPlaylist.stringValue = [NSString stringWithFormat:@"Playlist ended"];
    });
}

void stateChangedCallback(void *user, ssp_player_state_t state) {
    runOnMainQueueWithoutDeadlocking(^{
        mainViewController.lblState.stringValue = [NSString stringWithFormat:@"Player state: %d", state];
    });
}

- (void)viewDidLoad {
    [super viewDidLoad];
    mainViewController = self;
    [self initializePlayer];
}

- (void)checkForError:(SSP_ERROR)error str:(NSString *)str{
    if(error != SSP_OK) {
        NSString *message = [NSString stringWithFormat:@"An error occured in libssp_player:\n%@\nError code: %d", str, error];
        NSString *log = [NSString stringWithFormat:@"libssp_player error: [%@] code: [%d]", str, error];
        NSLog(@"%@", log);
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:message];
        [alert runModal];
    }
}

- (void)initializePlayer {
    int version = SSP_GetVersion();
    NSLog(@"libssp_player version: %d", version);

    NSFileManager* fileManager = [[NSFileManager alloc] init];
    NSString* path = [fileManager currentDirectoryPath];
    SSP_ERROR error = SSP_Init([path UTF8String]);
    [self checkForError:error str:@"SSP_Init"];

    SSP_SetLogCallback(logCallback, NULL);
    //SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, (__bridge_retained void *)self); // eventually crashes the app
    SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, NULL);
    SSP_SetPlaylistEndedCallback(playlistEndedCallback, NULL);
    SSP_SetStateChangedCallback(stateChangedCallback, NULL);

    int deviceCount = SSP_GetOutputDeviceCount();
    SSP_DEVICE** devices = malloc(sizeof(SSP_DEVICE*) * deviceCount);
    for(int a = 0; a < deviceCount; a++) {
//        SSP_DEVICE tempDevice;
//        SSP_GetOutputDevice(a, &tempDevice);
//        NSLog(@"Detected device --> id: %d name: %s driver: %s isDefault: %d isInitialized: %d", tempDevice.deviceId, tempDevice.name, tempDevice.driver, tempDevice.isDefault, tempDevice.isInitialized);

        devices[a] = malloc(sizeof(SSP_DEVICE));
        SSP_GetOutputDevice(a, devices[a]);
    }

    error = SSP_InitDevice(-1, 44100, 1000, 100, true);
    [self checkForError:error str:@"SSP_InitDevice"];

    SSP_DEVICE device;
    SSP_GetDevice(&device);

    SSP_EQPRESET preset;
    SSP_ResetEQPreset(&preset);
    preset.name = "Hello world";
    preset.bands[0].gain = 4;
    preset.bands[1].gain = 4;
    preset.bands[2].gain = 4;
    preset.bands[3].gain = 3;
    preset.bands[4].gain = 2;
    preset.bands[5].gain = 1;
    preset.bands[6].gain = 0;
    preset.bands[7].gain = 0;
    preset.bands[8].gain = 4;
    preset.bands[9].gain = 4;
    preset.bands[10].gain = 3;
    preset.bands[11].gain = 2;
    preset.bands[12].gain = 1;
    preset.bands[13].gain = 1;
    preset.bands[14].gain = 0;
    preset.bands[15].gain = 4;
    preset.bands[16].gain = 4;
    preset.bands[17].gain = 2;
    SSP_SetEQPreset(&preset);
    SSP_SetEQEnabled(true);
    SSP_NormalizeEQ();
    SSP_EQPRESET presetNormalized;
    SSP_GetEQPreset(&presetNormalized);

    NSLog(@"Player initialization successful!");
}

- (void)timerRefreshPositionElapsed {
    SSP_POSITION pos;
    SSP_GetPosition(&pos);
    self.lblPosition.stringValue = [NSString stringWithFormat:@"Position: %s", pos.str];
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

    // Make sure player is stopped
    SSP_ERROR error;
    if(SSP_GetState() == SSP_PLAYER_STATE_PLAYING) {
        error = SSP_Stop();
        [self checkForError:error str:@"SSP_Stop"];
    }

    error = SSP_Playlist_Clear();
    [self checkForError:error str:@"SSP_Playlist_Clear"];

    if([panel runModal] == NSModalResponseOK) {
        for(int a = 0; a < panel.URLs.count; a++) {
            NSURL *url = [panel.URLs objectAtIndex:a];
            error = SSP_Playlist_AddItem((char *)[url.path UTF8String]);
            [self checkForError:error str:@"SSP_Playlist_AddItem"];
        }
    }
}

- (IBAction)actionClose:(id)sender {
    if(SSP_GetState() != SSP_PLAYER_STATE_STOPPED) {
        SSP_Stop();
    }
    SSP_Free();
    [NSApp terminate:self];
}

- (IBAction)actionPlay:(id)sender {
    SSP_ERROR error = SSP_Play();
    [self checkForError:error str:@"SSP_Play"];
    timerRefreshPosition = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(timerRefreshPositionElapsed) userInfo:nil repeats:YES];
}

- (IBAction)actionPause:(id)sender {
    SSP_ERROR error = SSP_Pause();
    [self checkForError:error str:@"SSP_Pause"];}

- (IBAction)actionStop:(id)sender {
    SSP_ERROR error = SSP_Stop();
    [self checkForError:error str:@"SSP_Stop"];
    [timerRefreshPosition invalidate];
}

- (IBAction)actionPrevious:(id)sender {
    SSP_ERROR error = SSP_Previous();
    [self checkForError:error str:@"SSP_Previous"];}

- (IBAction)actionNext:(id)sender {
    SSP_ERROR error = SSP_Next();
    [self checkForError:error str:@"SSP_Next"];
}

@end
