//
//  ViewController.h
//  player-sample-osx
//
//  Created by Yanick Castonguay on 2015-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController

@property (weak) IBOutlet NSTextField *lblFilePath;
@property (weak) IBOutlet NSTextField *lblPosition;
@property (weak) IBOutlet NSTextField *lblPlaylist;
- (IBAction)actionOpenAudioFiles:(id)sender;
- (IBAction)actionClose:(id)sender;

@end

