//
//  NetworkWindowController.h
//  DriveWire
//
//  Created by Boisy Pitre on 4/19/15.
//
//

@interface NetworkWindowController : NSWindowController

@property (assign) IBOutlet NSScrollView *scrollView;

- (id)initWithChannels:(NSArray *)channels;

@end
