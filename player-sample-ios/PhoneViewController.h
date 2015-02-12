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

