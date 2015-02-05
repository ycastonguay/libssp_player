//
//  PhoneViewController.h
//  player-sample-ios
//
//  Created by Yanick Castonguay on 2015-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PhoneViewController : UIViewController
@property (weak, nonatomic) IBOutlet UILabel *lblTitle;
@property (weak, nonatomic) IBOutlet UILabel *lblVersion;
@property (weak, nonatomic) IBOutlet UILabel *lblState;
@property (weak, nonatomic) IBOutlet UILabel *lblPlaylist;
@property (weak, nonatomic) IBOutlet UILabel *lblFilePath;
@property (weak, nonatomic) IBOutlet UILabel *lblPosition;
- (IBAction)actionPause:(id)sender;
- (IBAction)actionPlay:(id)sender;
- (IBAction)actionStop:(id)sender;
- (IBAction)actionPrevious:(id)sender;
- (IBAction)actionNext:(id)sender;

@end

