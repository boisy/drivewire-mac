//
//  VirtualSerialChannel+DWCommands.m
//  
//
//  Created by Boisy Pitre on 4/23/15.
//
//

#import "VirtualSerialChannel+DWCommands.h"
#import "DriveWireServerModel.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"

@implementation VirtualSerialChannel (DWCommands)

#pragma mark -
#pragma mark DW Command Handlers

- (NSError *)handleDWSERVER:(NSArray *)array;
{
    NSError *error = nil;
    BOOL showHelp = TRUE;
    
    if ([array count] > 0)
    {
        NSDictionary *commandDictionary = @{@"cmd"          : @"handleDWSERVERCMD:",
                                            @"dir"          : @"handleDWSERVERDIR:",
                                            @"list"         : @"handleDWSERVERLIST:",
                                            @"terminate"    : @"handleDWSERVERTERMINATE:",
                                            };

        NSString *command = [array objectAtIndex:0];
        NSString *selectorString = [commandDictionary objectForKey:command];
        if (nil != selectorString)
        {
            SEL selector = NSSelectorFromString(selectorString);
            error = [self performSelector:selector withObject:[array subarrayWithRange:NSMakeRange(1, [array count] - 1)]];
            showHelp = FALSE;
        }
    }
    
    if (showHelp == TRUE)
    {
        // show help
        NSData *data = [@"dw server commands:\x0A\x0D"
                        "    list <file or url> - list contents of file\x0A\x0D"
                        "    dir  <path>        - list the contents of the directory at path\x0A\x0D"
                        "    terminate [force]  - shut down server\x0A\x0D"
                        dataUsingEncoding:NSASCIIStringEncoding];
        [self.incomingBuffer appendData:data];
    }
    
    return error;
}


- (NSError *)handleDWSERVERTERMINATE:(NSArray *)array;
{
    NSError *error = nil;
    
    NSData *data = [@"Server shutdown requested.\x0A\x0D" dataUsingEncoding:NSASCIIStringEncoding];
    
    [self.incomingBuffer appendData:data];
    
    [NSApp performSelector:@selector(terminate:) withObject:nil afterDelay:5.0];

    return error;
}

- (NSError *)handleDWSERVERLIST:(NSArray *)array;
{
    NSError *error = nil;
    BOOL showHelp = TRUE;
    
    if ([array count] > 0)
    {
        showHelp = FALSE;
        
        NSString *file = [array objectAtIndex:0];
        NSData *data;
        
        if( [file hasPrefix:@"http://"]  || [file hasPrefix:@"ftp://"] )
        {
            NSURL *url = [NSURL URLWithString:file];
            data = [NSData dataWithContentsOfURL:url options:0 error:&error];
        }
        else if ([file characterAtIndex:0] != '/')
        {
            // assume this is relative to the home directory
            file = [NSString stringWithFormat:@"%@/%@", NSHomeDirectory(), file];
            data = [NSData dataWithContentsOfFile:file];
        }
        else
        {
            data = [NSData dataWithContentsOfFile:file];
        }

        
        if (nil == data)
        {
            if( nil == error)
            {
                data = [@"Error: file not found\x0A\x0D" dataUsingEncoding:NSASCIIStringEncoding];
            }
            else
            {
                data = [[NSString stringWithFormat:@"Error: %@\x0A\x0D", [error localizedDescription]] dataUsingEncoding:NSNonLossyASCIIStringEncoding];
            }
        }
        
        [self.incomingBuffer appendData:data];
    }
    
    if (showHelp == TRUE)
    {
        // show help
        NSData *data = [@"Usage: dw server list <file or url>\x0A\x0D"
                        dataUsingEncoding:NSASCIIStringEncoding];
        [self.incomingBuffer appendData:data];
    }
    
    return error;
}

- (NSError *)handleDWSERVERCMD:(NSArray *)array;
{
    NSError *error = nil;
    BOOL showHelp = TRUE;
    
    if ([array count] > 0)
    {
        showHelp = FALSE;
        
        NSString *commandToRun = [[array valueForKey:@"description"] componentsJoinedByString:@" "];

        NSTask *task = [[NSTask alloc] init];
        [task setLaunchPath:@"/bin/sh"];
        
        NSArray *arguments = [NSArray arrayWithObjects:
                              @"-c" ,
                              [NSString stringWithFormat:@"%@", commandToRun],
                              nil];
        [task setArguments:arguments];
        
        NSPipe *pipe = [NSPipe pipe];
        [task setStandardOutput:pipe];
        [task setStandardError:pipe];

        NSFileHandle *file = [pipe fileHandleForReading];
        
        [task launch];

        // setup a termination time
        NSDate *terminateDate = [[NSDate date] dateByAddingTimeInterval:5.0];
        while ((task != nil) && ([task isRunning]))
        {
            if ([[NSDate date] compare:(id)terminateDate] == NSOrderedDescending)
            {
                [task terminate];
            }

            [NSThread sleepForTimeInterval:1.0];
        }
        
        NSData *data = [file readDataToEndOfFile];

        if ([data length] > 0)
        {
            NSString *blob = [NSString stringWithCString:[data bytes] encoding:NSASCIIStringEncoding];
            NSArray *lines = [blob componentsSeparatedByString:@"\x0A"];
            
            for (NSString *line in lines)
            {
                NSString *newLine = [NSString stringWithFormat:@"%@\x0A\x0D", line];
                data = [newLine dataUsingEncoding:NSASCIIStringEncoding];
                [self.incomingBuffer appendData:data];
            }
        }
    }
    
    if (showHelp == TRUE)
    {
        // show help
        NSData *data = [@"Usage: dw server cmd <host_command> <params...>\x0A\x0D"
                        dataUsingEncoding:NSASCIIStringEncoding];
        [self.incomingBuffer appendData:data];
    }
    
    return error;
}

- (NSError *)handleDWSERVERDIR:(NSArray *)array;
{
    NSError *error = nil;
    BOOL showHelp = TRUE;
    
    NSString *path = @".";
    
    if ([array count] > 0)
    {
        path = [array objectAtIndex:0];
    }

    if ([path characterAtIndex:0] != '/')
    {
        // assume this is relative to the home directory
        path = [NSString stringWithFormat:@"%@/%@", NSHomeDirectory(), path];
    }

    showHelp = FALSE;
    
    // capture directory contents
    NSArray *files = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path error:&error];
    for (NSString *file in files)
    {
        NSData *data = [[NSString stringWithFormat:@"%@\x0A\x0D", file]
                        dataUsingEncoding:NSASCIIStringEncoding];
        [self.incomingBuffer appendData:data];
    }

    return error;
}

- (NSError *)handleDWTEST:(NSArray *)array;
{
    NSError *error = nil;
    
    [self.incomingBuffer appendData:[@"TEST RESPONSE\x0D\x0A"
                                     dataUsingEncoding:NSASCIIStringEncoding]];

    return error;
}

- (NSError *)handleDWDISK:(NSArray *)array;
{
    NSError *error = nil;
    BOOL showHelp = TRUE;
    
    if ([array count] > 0)
    {
        NSDictionary *commandDictionary = @{@"show"          : @"handleDWDISKSHOW:",
                                            };
        
        NSString *command = [array objectAtIndex:0];
        NSString *selectorString = [commandDictionary objectForKey:command];
        if (nil != selectorString)
        {
            SEL selector = NSSelectorFromString(selectorString);
            error = [self performSelector:selector withObject:[array subarrayWithRange:NSMakeRange(1, [array count] - 1)]];
            showHelp = FALSE;
        }
    }
    
    if (showHelp == TRUE)
    {
        // show help
        NSData *data = [@"dw disk commands:\x0A\x0D"
                        "    show [#] - Show current disk details\x0A\x0D"
                        dataUsingEncoding:NSASCIIStringEncoding];
        [self.incomingBuffer appendData:data];
    }
    
    return error;
}

- (NSError *)handleDWDISKSHOW:(NSArray *)array;
{
    NSError *error = nil;

    BOOL showHelp = TRUE;
    
    if ([array count] > 0)
    {
        showHelp = FALSE;
        NSInteger requestedSlot = [[array objectAtIndex:0] integerValue];
        
        if( requestedSlot >=0 && requestedSlot <=4 )
        {
            DriveWireServerModel *dwsm = (DriveWireServerModel *)[self delegate];
            NSArray *driveArray = dwsm.driveArray;
            VirtualDriveController *controller = [driveArray objectAtIndex:requestedSlot];
            
            [self.incomingBuffer appendData:[[NSString stringWithFormat:@"Details for disk in drive #%lu\x0D\x0A", requestedSlot] dataUsingEncoding:NSASCIIStringEncoding]];

            if( [controller isEmpty])
            {
                [self.incomingBuffer appendData:[@"Is empty\x0D\x0A" dataUsingEncoding:NSASCIIStringEncoding]];
            }
            else
            {
                [self.incomingBuffer appendData:[[NSString stringWithFormat:@"%@\x0D\x0A", [controller cartridgePath]] dataUsingEncoding:NSASCIIStringEncoding]];
                
                [self.incomingBuffer appendData:[[NSString stringWithFormat:@"Total Sectors Read: %d\x0D\x0A", controller.totalSectorsRead] dataUsingEncoding:NSASCIIStringEncoding]];
                
                [self.incomingBuffer appendData:[[NSString stringWithFormat:@"Total Sectors Written: %d\x0D\x0A", controller.totalSectorsWritten] dataUsingEncoding:NSASCIIStringEncoding]];
            }
        }
        else
        {
            [self.incomingBuffer appendData:[@"Drive number out of range (0-3)\x0D\x0A" dataUsingEncoding:NSASCIIStringEncoding]];
        }
    }

    if (showHelp == TRUE)
    {
        // show help
        NSData *data = [@"Usage: dw disk show [#]:\x0A\x0D"
                        "    Number is disk drive to show info for.\x0A\x0D"
                        dataUsingEncoding:NSASCIIStringEncoding];
        [self.incomingBuffer appendData:data];
    }
    
    return error;
}

- (NSError *)handleDWUI:(NSArray *)array;
{
    NSError *error = nil;
    
    return error;
}

- (NSError *)handleDWCommand:(NSArray *)array;
{
    NSError *error = nil;
    BOOL showHelp = TRUE;

    NSDictionary *commandDictionary = @{@"disk"    : @"handleDWDISK:",
                                        @"ui"      : @"handleDWUI:",
                                        @"test"    : @"handleDWTEST:",
                                        @"server"  : @"handleDWSERVER:"
                                        };
    
    if ([array count] > 1)
    {
        NSString *command = [array objectAtIndex:1];
        NSString *selectorString = [commandDictionary objectForKey:command];
        if (nil != selectorString)
        {
            showHelp = FALSE;
            SEL selector = NSSelectorFromString(selectorString);
            error = [self performSelector:selector withObject:[array subarrayWithRange:NSMakeRange(2, [array count] - 2)]];
        }
    }

    if (showHelp == TRUE)
    {
        // only 'dw' command, send help
        NSData *data = [@"dw commands:\x0A\x0D"
                        "    disk        - commands related to disk images\x0A\x0D"
                        "    server      - commands related to the server\x0A\x0D"
                        "    ui          - commands related to the user interface\x0A\x0D"
                        dataUsingEncoding:NSASCIIStringEncoding];
        [self.incomingBuffer appendData:data];
    }
    
    self.shouldClose = TRUE;
    return error;
}

#pragma clang diagnostic pop

@end
