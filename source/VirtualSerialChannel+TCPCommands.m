//
//  VirtualSerialChannel+TCPCommands.m
//  DriveWire
//
//  Created by Boisy Pitre on 4/23/15.
//
//

#import "VirtualSerialChannel+TCPCommands.h"

@implementation VirtualSerialChannel (TCPCommands)

#pragma mark -
#pragma mark TCP Command Handlers

- (NSError *)handleTCPConnect:(NSArray *)array;
{
    NSError *error = nil;
    
    if ([array count] >= 3)
    {
        NSString *host = [array objectAtIndex:1];
        NSString *port = [array objectAtIndex:2];
        
        dispatch_queue_t dQ = dispatch_queue_create("delegate_queue", nil);
        dispatch_queue_t sQ = dispatch_queue_create("socket_queue", nil);
        
        self.connectedSocket = [[GCDAsyncSocket alloc] initWithDelegate:self
                                                 delegateQueue:dQ
                                                   socketQueue:sQ];
        [self.connectedSocket connectToHost:host onPort:[port integerValue] error:&error];
    }
    
    return error;
}

- (NSError *)handleTCPListen:(NSArray *)array;
{
    NSError *error = nil;
    
    return error;
}

- (NSError *)handleTCPJoin:(NSArray *)array;
{
    NSError *error = nil;
    
    return error;
}

- (NSError *)handleTCPKill:(NSArray *)array;
{
    NSError *error = nil;
    
    [self.connectedSocket disconnect];
    self.connectedSocket = nil;

    return error;
}

- (NSError *)handleTCPCommand:(NSArray *)array;
{
    NSError *error = nil;
    
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
            error = [self performSelector:selector withObject:[array subarrayWithRange:NSMakeRange(1, [array count] - 1)]];
        }
    }
    
    return error;
}

@end
