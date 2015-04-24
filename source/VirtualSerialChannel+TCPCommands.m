//
//  VirtualSerialChannel+TCPCommands.m
//  DriveWire MacServer
//
//  Created by Boisy Pitre on 4/23/15.
//
//

#import "VirtualSerialChannel+TCPCommands.h"

@implementation VirtualSerialChannel (TCPCommands)

#pragma mark -
#pragma mark TCP Command Handlers

- (void)handleTCPConnect:(NSArray *)array;
{
    
}

- (void)handleTCPListen:(NSArray *)array;
{
    
}

- (void)handleTCPJoin:(NSArray *)array;
{
    
}

- (void)handleTCPKill:(NSArray *)array;
{
    
}
- (void)handleTCPCommand:(NSArray *)array;
{
    NSDictionary *commandDictionary = @{@"connect" : @"handleTCPConnect:",
                                        @"listen"  : @"handleTCPListen:",
                                        @"join"    : @"handleTCPJoin:",
                                        @"kill"    : @"handleTCPKill:"};
    
    if ([array count] > 1)
    {
        NSString *command = [array objectAtIndex:1];
        NSString *selectorString = [commandDictionary objectForKey:command];
        if (nil != selectorString)
        {
            SEL selector = NSSelectorFromString(selectorString);
            [self performSelector:selector withObject:[array subarrayWithRange:NSMakeRange(1, [array count] - 1)]];
        }
    }
}

@end
