//
//  NetworkConnectionViewController.h
//  DriveWire
//
//  Created by Boisy Pitre on 4/19/15.
//
//

#import <Cocoa/Cocoa.h>
#import <TeeBoy/TBLEDView.h>
#import "VirtualSerialChannel.h"

@interface NetworkConnectionViewController : NSViewController <VirtualSerialChannelDelegate>

@property (strong) NSString *name;
@property (strong) NSString *status;
@property (assign) IBOutlet TBLEDView *incomingLED;
@property (assign) IBOutlet TBLEDView *outgoingLED;
@property (strong) VirtualSerialChannel *channel;

- (id)initWithChannel:(VirtualSerialChannel *)channel;

@end
