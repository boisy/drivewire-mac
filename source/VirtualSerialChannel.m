//
//  VirtualSerialChannel.m
//  DriveWire MacServer
//
//  Created by Boisy Pitre on 4/15/15.
//
//

#import "VirtualSerialChannel.h"
#import "VirtualSerialChannel+DWCommands.h"
#import "VirtualSerialChannel+TCPCommands.h"
#import "VirtualSerialChannel+ATCommands.h"
#import "GCDAsyncSocket.h"

#define READ_TIMEOUT   0.0
#define WRITE_TIMEOUT   0.0

enum {OUTGOING_DATA_WRITTEN};

typedef enum {VMODE_COMMAND, VMODE_PASSTHRU, VMODE_TCP_SERVER, VMODE_TCP_CLIENT} VirtualSerialMode;

@interface VirtualSerialChannel ()

@property (strong) GCDAsyncSocket *serverSocket;
@property (strong) GCDAsyncSocket *connectedSocket;
@property (assign) VirtualSerialMode mode;

@end

@implementation VirtualSerialChannel

#pragma mark -
#pragma mark GCDAsyncSocket Delegate Methods

- (void)socket:(GCDAsyncSocket *)sender didReadData:(NSData *)data withTag:(long)tag;
{
    [self.incomingBuffer appendData:data];
    [self.delegate didReceiveData:self];
}

- (void)socket:(GCDAsyncSocket *)sender didWriteDataWithTag:(long)tag;
{
    switch (tag)
    {
        case OUTGOING_DATA_WRITTEN:
            self.outgoingBuffer.length = 0;
            [self.delegate didSendData:self];
            break;
    }
}

- (void)socket:(GCDAsyncSocket *)sender didAcceptNewSocket:(GCDAsyncSocket *)newSocket;
{
    self.connectedSocket = newSocket;
    [self.connectedSocket writeData:self.outgoingBuffer withTimeout:WRITE_TIMEOUT tag:OUTGOING_DATA_WRITTEN];
    [self.delegate didConnect:self];
}


#pragma mark -
#pragma mark Virtual Port Management Methods

- (void)open;
{
    self.waitCounter = 0;
    self.incomingBuffer = [NSMutableData data];
    self.outgoingBuffer = [NSMutableData data];
    
    self.mode = VMODE_COMMAND;
}

- (void)close;
{
    self.incomingBuffer = nil;
    self.outgoingBuffer = nil;
    
    [self.serverSocket disconnect];
    [self.delegate didDisconnect:self];
    self.serverSocket = nil;
}

- (BOOL)hasData;
{
    return [self.incomingBuffer length] > 0;
}

- (NSUInteger)availableToRead;
{
    return [self.incomingBuffer length];
}

- (u_char)getByte;
{
    u_char result = 0;
    
    if ([self hasData])
    {
        result = *(u_char *)[self.incomingBuffer bytes];
        [self.incomingBuffer replaceBytesInRange:NSMakeRange(0, 1) withBytes:nil length:0];
    }
    
    return result;
}

- (NSData *)getNumberOfBytes:(NSUInteger)count;
{
    NSData *result = nil;
    NSUInteger available = [self availableToRead];
    if (count > available)
    {
        count = available;
    }
    
    // get data directly from channel's incoming buffer
    result = [self.incomingBuffer subdataWithRange:NSMakeRange(0, count)];
    [self.incomingBuffer replaceBytesInRange:NSMakeRange(0, count) withBytes:nil length:0];
    
    return result;
}

- (void)putByte:(u_char)byte;
{
    switch (self.mode)
    {
        case VMODE_COMMAND:
            if (byte == '\x0D')
            {
                // we have a complete command -- parse it
                [self parseTopLevelCommand:self.outgoingBuffer];
                [self.outgoingBuffer setLength:0];
            }
            else
            {
                [self.outgoingBuffer appendBytes:&byte length:1];
            }
            break;
            
        case VMODE_PASSTHRU:
            [self.connectedSocket writeData:self.outgoingBuffer withTimeout:WRITE_TIMEOUT tag:OUTGOING_DATA_WRITTEN];
            break;
            
        case VMODE_TCP_CLIENT:
            [self.outgoingBuffer appendBytes:&byte length:1];
            break;
            
        case VMODE_TCP_SERVER:
            [self.outgoingBuffer appendBytes:&byte length:1];
            break;
    }
}

- (void)putBytes:(u_char *)bytes length:(NSUInteger)length;
{
    [self.outgoingBuffer appendBytes:bytes length:length];
    [self.connectedSocket writeData:self.outgoingBuffer withTimeout:WRITE_TIMEOUT tag:OUTGOING_DATA_WRITTEN];
}


#pragma mark -
#pragma mark Top Level Command Handler

// parse the string data represented by the passed NSData buffer
- (void)parseTopLevelCommand:(NSData *)buffer;
{
    NSString *string = [[[NSString alloc] initWithData:buffer encoding:NSASCIIStringEncoding] lowercaseString];
    
    NSArray *array = [[string stringByTrimmingCharactersInSet:
                      [NSCharacterSet whitespaceCharacterSet]] componentsSeparatedByString:@" "];
    
    // setup command array
    NSDictionary *commandDictionary = @{@"tcp" : @"handleTCPCommand:",
                                        @"at"  : @"handleATCommand:",
                                        @"dw"  : @"handleDWCommand:"
                               };

    // append SUCCESS line
    [self.incomingBuffer appendData:[@"S\x0D" dataUsingEncoding:NSASCIIStringEncoding]];
    
    if ([array count] > 0)
    {
        NSString *command = [array objectAtIndex:0];
        NSString *selectorString = [commandDictionary objectForKey:command];
        if (nil != selectorString)
        {
            SEL selector = NSSelectorFromString(selectorString);
            [self performSelector:selector withObject:array];
        }
    }
}


#pragma mark -
#pragma mark Init/Dealloc Methods

- (id)initWithNumber:(NSUInteger)number port:(NSUInteger)port;
{
    if (self = [super init])
    {
        self.number = number;
        self.port = port;
        
        self.serverSocket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
        
        NSError *error = nil;
        [self.serverSocket acceptOnPort:self.port error:&error];
    }
    
    return self;
}

- (void)dealloc;
{
    self.delegate = nil;
    [self close];
}

@end
