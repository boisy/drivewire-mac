//
//  VirtualSerialChannel.h
//  DriveWire MacServer
//
//  Created by Boisy Pitre on 4/15/15.
//
//

#import <Foundation/Foundation.h>
#import <CocoaAsyncSocket/GCDAsyncSocket.h>

@class VirtualSerialChannel;

@protocol VirtualSerialChannelDelegate

- (void)didConnect:(VirtualSerialChannel *)channel;
- (void)didDisconnect:(VirtualSerialChannel *)channel;
- (void)didSendData:(VirtualSerialChannel *)channel;
- (void)didReceiveData:(VirtualSerialChannel *)channel;

@end

@interface VirtualSerialChannel : NSObject <GCDAsyncSocketDelegate>

@property (assign) NSUInteger number;
@property (assign) NSUInteger port;
@property (strong) GCDAsyncSocket *socket;
@property (strong) NSMutableData *incomingBuffer; // incoming TO CoCo
@property (strong) NSMutableData *outgoingBuffer; // outgoing FROM CoCo
@property (assign) NSUInteger waitCounter;
@property (assign) id<VirtualSerialChannelDelegate> delegate;
@property (assign) BOOL shouldClose;

- (id)initWithNumber:(NSUInteger)number port:(NSUInteger)port;

- (BOOL)hasData;
- (NSUInteger)availableToRead;
- (u_char)getByte;
- (NSData *)getNumberOfBytes:(NSUInteger)count;
- (void)putByte:(u_char)byte;
- (void)putBytes:(u_char *)bytes length:(NSUInteger)length;

- (void)open;
- (void)close;

@end
