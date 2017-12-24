//
//  NetworkTableViewController.m
//  DriveWire
//
//  Created by Boisy Pitre on 12/22/17.
//

#import "NetworkTableViewController.h"
#import "DriveWireDocument.h"
#import <TeeBoy/TBLEDView.h>

@implementation NetworkTableViewController

#pragma mark -
#pragma mark Notification Methods

- (void)channelConnected:(NSNotification *)note;
{
    VirtualSerialChannel *channel = [note.userInfo objectForKey:@"channel"];
    dispatch_async(dispatch_get_main_queue(), ^{
        NSTableCellView *selectedCell = [self.tableView
                                     viewAtColumn:1
                                     row:channel.number - 1
                                     makeIfNecessary:NO];
        selectedCell.textField.stringValue = @"Connected";
    });
}

- (void)channelDisconnected:(NSNotification *)note;
{
    VirtualSerialChannel *channel = [note.userInfo objectForKey:@"channel"];
    dispatch_async(dispatch_get_main_queue(), ^{
        NSTableCellView *selectedCell = [self.tableView
                                        viewAtColumn:1
                                        row:channel.number - 1
                                        makeIfNecessary:NO];
        selectedCell.textField.stringValue = @"Disconnected";
    });
}

- (void)dataSent:(NSNotification *)note;
{
    VirtualSerialChannel *channel = [note.userInfo objectForKey:@"channel"];
    dispatch_async(dispatch_get_main_queue(), ^{
        NSTextField *selectedCell = [self.tableView
                                     viewAtColumn:2
                                     row:channel.number - 1
                                     makeIfNecessary:NO];
        TBLEDView *v = [[selectedCell subviews] objectAtIndex:0];
        [v blink];
    });
}

- (void)dataReceived:(NSNotification *)note;
{
    VirtualSerialChannel *channel = [note.userInfo objectForKey:@"channel"];
    dispatch_async(dispatch_get_main_queue(), ^{
        NSTextField *selectedCell = [self.tableView
                                     viewAtColumn:3
                                     row:channel.number - 1
                                     makeIfNecessary:NO];
        TBLEDView *v = [[selectedCell subviews] objectAtIndex:0];
        [v blink];
    });
}


#pragma mark -
#pragma mark Init/Dealloc Methods

- (void)viewWillAppear;
{
    [super viewWillAppear];
    DriveWireDocument *document = self.view.window.windowController.document;
    DriveWireServerModel *model = document.dwModel;
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(channelConnected:) name:kVirtualChannelConnectedNotification
                                               object:model];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(channelDisconnected:) name:kVirtualChannelDisconnectedNotification
                                               object:model];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(dataSent:) name:kVirtualChannelDataSentNotification
                                               object:model];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(dataReceived:) name:kVirtualChannelDataReceivedNotification
                                               object:model];
}

- (void)viewWillDisappear;
{
    [super viewWillDisappear];
    DriveWireDocument *document = self.view.window.windowController.document;
    DriveWireServerModel *model = document.dwModel;
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kVirtualChannelConnectedNotification
                                                  object:model];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kVirtualChannelDisconnectedNotification
                                                  object:model];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kVirtualChannelDataSentNotification
                                                  object:model];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kVirtualChannelDataReceivedNotification
                                                  object:model];
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
{
    DriveWireDocument *d = self.tableView.window.windowController.document;
    return [d.dwModel.serialChannels count];
}

- (NSView *)tableView:(NSTableView *)tableView
   viewForTableColumn:(NSTableColumn *)tableColumn
                  row:(NSInteger)row
{
    // Get an existing cell with the MyView identifier if it exists
    NSTableCellView *result = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    
    // There is no existing cell to reuse so create a new one
    if (result == nil) {
        
    }
    
    // result is now guaranteed to be valid, either as a reused cell
    // or as a new cell, so set the stringValue of the cell to the
    // nameArray value at row
    DriveWireDocument *d = self.tableView.window.windowController.document;
    
    if ([tableColumn.identifier isEqualToString:@"no"])
    {
        VirtualSerialChannel *channel = [d.dwModel.serialChannels objectAtIndex:row];
        result.textField.stringValue = [NSString stringWithFormat:@"%ld", channel.number];
    }
    else
    if ([tableColumn.identifier isEqualToString:@"state"])
    {
        VirtualSerialChannel *channel = [d.dwModel.serialChannels objectAtIndex:row];
        result.textField.stringValue = @"Disconnected";
    
    }
    else
    if ([tableColumn.identifier isEqualToString:@"read"])
    {
        VirtualSerialChannel *channel = [d.dwModel.serialChannels objectAtIndex:row];
        TBLEDView *v = [[result subviews] objectAtIndex:0];
        [v blink];
    }

    // Return the result
    return result;
}

@end
