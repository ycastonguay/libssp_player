//
//  DesktopViewController.h
//  player-sample-osx
//
//  Created by Yanick Castonguay on 2015-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface DesktopViewController : NSViewController

@property (weak) IBOutlet NSTextField *lblFilePath;
@property (weak) IBOutlet NSTextField *lblPosition;
@property (weak) IBOutlet NSTextField *lblPlaylist;
@property (weak) IBOutlet NSTextField *lblState;
- (IBAction)actionOpenAudioFiles:(id)sender;
- (IBAction)actionClose:(id)sender;
- (IBAction)actionPlay:(id)sender;
- (IBAction)actionStop:(id)sender;
- (IBAction)actionPause:(id)sender;
- (IBAction)actionNext:(id)sender;
- (IBAction)actionPrevious:(id)sender;

@end

