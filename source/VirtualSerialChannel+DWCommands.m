//
//  VirtualSerialChannel+DWCommands.m
//  
//
//  Created by Boisy Pitre on 4/23/15.
//
//

#import "VirtualSerialChannel+DWCommands.h"

@implementation VirtualSerialChannel (DWCommands)

#pragma mark -
#pragma mark DW Command Handlers

- (void)handleDWLIST:(NSArray *)array;
{
    if ([array count] > 1)
    {
        NSString *file = [array objectAtIndex:1];
        
        NSData *data = [NSData dataWithContentsOfFile:file];
        
        if (nil == data)
        {
            data = [@"Error: file not found\x0A\x0D"
                    dataUsingEncoding:NSASCIIStringEncoding];
        }
        
        [self.incomingBuffer appendData:data];
    }
    else
    {
        [self.incomingBuffer appendData:[@"Error: no file specified\x0A\x0D"
                                         dataUsingEncoding:NSASCIIStringEncoding]];
    }
}

- (void)handleDWTEST:(NSArray *)array;
{
    [self.incomingBuffer appendData:[@"TEST RESPONSE\x0D\x0A"
                                     dataUsingEncoding:NSASCIIStringEncoding]];
}

- (void)handleDWLoad:(NSArray *)array;
{
    
}

- (void)handleDWUI:(NSArray *)array;
{
    
}

- (void)handleDWCommand:(NSArray *)array;
{
    NSDictionary *commandDictionary = @{@"load"    : @"handleDWLoad:",
                                        @"ui"      : @"handleDWUI:",
                                        @"test"    : @"handleDWTEST:",
                                        @"list"    : @"handleDWLIST:"
                                        };
    
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
    else
    {
        // only 'dw' command, send help
        NSData *data = [@"DriveWire Server Help\x0A\x0D"
                        "This is cool\x0A\x0D"
                        dataUsingEncoding:NSASCIIStringEncoding];
        
        [self.incomingBuffer appendData:data];
    }
    
    self.shouldClose = TRUE;
}

@end
