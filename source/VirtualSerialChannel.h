//
//  VirtualSerialChannel.h
//  DriveWire MacServer
//
//  Created by Boisy Pitre on 4/15/15.
//
//

#import <Foundation/Foundation.h>

@interface VirtualSerialChannel : NSObject

@property (assign) NSUInteger number;
@property (strong) NSMutableData *incomingBuffer; // incoming TO CoCo
@property (strong) NSMutableData *outgoingBuffer; // outgoing FROM CoCo
@property (assign) NSUInteger waitCounter;

- (id)initWithNumber:(NSUInteger)number;

- (BOOL)hasData;
- (NSUInteger)availableToRead;
- (u_char)getByte;
- (NSData *)getNumberOfBytes:(NSUInteger)count;
- (void)putByte:(u_char)byte;
- (void)putBytes:(u_char *)bytes length:(NSUInteger)length;

- (void)open;
- (void)close;

@end
