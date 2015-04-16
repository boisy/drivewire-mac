/*
    File:       QFTPSendOperation.h

    Contains:   An NSOperation that runs an FTP request.
*/

#import "QRunLoopOperation.h"

/*
    QFTPSendOperation is a general purpose NSOperation that runs an FTP send request. 
    You initialise it with an FTP request and then, when you run the operation, 
    it sends the request and gathers the response.  It is quite a complex 
    object because it handles a wide variety of edge cases, but it's very 
    easy to use in simple cases:

    1. create the operation with the URL you want to get
    
    op = [[[QHFPSendOperation alloc] init] autorelease];
    
    2. set up any non-default parameters, for example, set the
       server, the path to put the data, the FTP data to send, the username and the password
    
    3. enqueue the operation
    
    [queue addOperation:op];
    
    4. finally, when the operation is done, use the error property to find out how things went
*/

enum {
    kSendBufferSize = 32768
};

@class QFTPSendOperation;

@protocol QFTPSendOperationDelegate

- (void)connectionWillOpen:(QFTPSendOperation *)operation;
- (void)connectionDidOpen:(QFTPSendOperation *)operation withError:(NSError *)error;
- (void)connection:(QFTPSendOperation *)operation didSendBytes:(NSUInteger)count;
- (void)connectionDidClose:(QFTPSendOperation *)operation withError:(NSError *)error;

@end

@interface QFTPSendOperation : QRunLoopOperation <NSStreamDelegate>
{
	NSString *						_server;
	NSString *						_path;
	NSString *						_username;
	NSString *						_password;
	BOOL							_passive;
    NSOutputStream *				_networkStream;
    NSInputStream *					_inputStream;
    uint8_t							_buffer[kSendBufferSize];
    size_t							_bufferOffset;
    size_t							_bufferLimit;
    NSUInteger						_cumulativeSize;
	id<QFTPSendOperationDelegate>	_delegate;
}

- (id)init;

// Things that are configured by the init method and can't be changed.

// Things you can configure before queuing the operation.

// runLoopThread and runLoopModdes inherited from QRunLoopOperation
@property (retain, readwrite) NSString *            server;
@property (retain, readwrite) NSString *            path;
@property (retain, readwrite) NSString *            username;
@property (retain, readwrite) NSString *            password;
@property (assign, readwrite) BOOL					passive;
@property (nonatomic, retain) NSInputStream *       inputStream;
@property (retain, readwrite) id<QFTPSendOperationDelegate>	delegate;

// Things you can configure up to the point where you start receiving data. 
// Typically you would change these in -connection:didReceiveResponse:, but 
// it is possible to change them up to the point where -connection:didReceiveData: 
// is called for the first time (that is, you could override -connection:didReceiveData: 
// and change these before calling super).

// IMPORTANT: If you set a response stream, QHTTPOperation calls the response 
// stream synchronously.  This is fine for file and memory streams, but it would 
// not work well for other types of streams (like a bound pair).

// Things that are only meaningful after the operation is finished.

// error property inherited from QRunLoopOperation
//@property (copy,   readonly)  NSError *             error;

@end
