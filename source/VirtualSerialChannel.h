//
//  VirtualSerialChannel.h
//  DriveWire
//
//  Created by Boisy Pitre on 4/15/15.
//
//

#import <Foundation/Foundation.h>
#import <CocoaAsyncSocket/GCDAsyncSocket.h>

#define READ_TIMEOUT   -1
#define WRITE_TIMEOUT   -1

enum {WRITETAG_DATA_WRITTEN, READTAG_DATA_READ, WRITETAG_TELNET_COMMANDS_WRITTEN, READTAG_TELNET_COMMAND_RESPONSES_READ};

@class VirtualSerialChannel;

@protocol VirtualSerialChannelDelegate

- (void)didConnect:(VirtualSerialChannel *)channel;
- (void)didDisconnect:(VirtualSerialChannel *)channel;
- (void)didSendData:(VirtualSerialChannel *)channel;
- (void)didReceiveData:(VirtualSerialChannel *)channel;

@end

typedef enum {VMODE_COMMAND, VMODE_PASSTHRU, VMODE_TCP_SERVER, VMODE_TCP_CLIENT} VirtualSerialMode;

@interface GlobalChannelArray : NSMutableArray

+ (NSMutableArray *)sharedArray;

@end

@interface VirtualSerialChannel : NSObject <GCDAsyncSocketDelegate>

@property (assign) BOOL telnetMode;
@property (assign) NSUInteger number;
@property (assign) NSUInteger port;
@property (strong) GCDAsyncSocket *clientSocket; // for outgoing connection
@property (strong) NSMutableArray *listenSockets;
@property (strong) GCDAsyncSocket *serverSocket;
@property (strong) NSMutableData *incomingBuffer; // incoming TO CoCo
@property (strong) NSMutableData *outgoingBuffer; // outgoing FROM CoCo
@property (assign) NSUInteger waitCounter;
@property (weak) id<VirtualSerialChannelDelegate> delegate;
@property (assign) BOOL shouldClose;
@property (assign) VirtualSerialMode mode;
@property (strong) NSData *telnetCommands;

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
