//
//  NetworkWindowController.m
//  DriveWire
//
//  Created by Boisy Pitre on 4/19/15.
//
//

#import "NetworkWindowController.h"
#import "NetworkConnectionViewController.h"

@interface NetworkWindowController ()

@property (strong) NSArray *virtualChannels;

@end

@implementation NetworkWindowController

- (id)initWithChannels:(NSArray *)channels;
{
    if (self = [super initWithWindowNibName:@"NetworkWindowController"])
    {
        self.virtualChannels = channels;
    }
    
    return self;
}

- (void)windowDidLoad;
{
    [super windowDidLoad];

    NSUInteger totalHeight = 0;
    for (int i = 0; i < 15; i++)
    {
        NetworkConnectionViewController *vc = [[NetworkConnectionViewController alloc] initWithChannel:[self.virtualChannels objectAtIndex:15 - i]];
        NSRect frame = vc.view.frame;
        frame.origin.y = frame.size.height * i;
        totalHeight += frame.size.height;
        vc.view.frame = frame;
        [self.scrollView.contentView addSubview:vc.view];
    }

//    NSSize scrollContentSize = self.scrollView.documentView.frame.size;
//    scrollContentSize.height = totalHeight;
//    [self.scrollView.documentView setFrameSize:scrollContentSize];
}

@end
