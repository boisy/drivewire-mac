//
//  VSerialChannel.m
//  DriveWire MacServer
//
//  Created by Boisy Pitre on 4/15/15.
//
//

#import "VSerialChannel.h"

@implementation VSerialChannel

- (void)open;
{
    self.waitCounter = 0;
    self.incomingBuffer = [NSMutableData data];
    self.outgoingBuffer = [NSMutableData data];
}

- (void)close;
{
    self.incomingBuffer = nil;
    self.outgoingBuffer = nil;
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
        [self.incomingBuffer replaceBytesInRange:NSMakeRange(0, 1) withBytes:NULL];
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
    [self.incomingBuffer replaceBytesInRange:NSMakeRange(0, count) withBytes:NULL];
    
    return result;
}

- (void)putByte:(u_char)byte;
{
    [self.outgoingBuffer appendBytes:&byte length:1];
}

- (void)putBytes:(u_char *)bytes length:(NSUInteger)length;
{
    [self.outgoingBuffer appendBytes:bytes length:length];
}

- (id)initWithNumber:(NSUInteger)number;
{
    if (self = [super init])
    {
        self.number = number;
    }
    
    return self;
}

- (void)dealloc;
{
    [self close];
}

@end
