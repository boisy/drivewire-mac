//--------------------------------------------------------------------------------------------------
//
//  Copyright (c) 2010-2013 Tee-Boy
//
//  This source code and specific concepts contained herein are Confidential
//  Information and Property of Tee-Boy.
//  Distribution is prohibited without written permission of Tee-Boy.
//
//--------------------------------------------------------------------------------------------------
//
//  Tee-Boy                                http://www.tee-boy.com/
//  441 Saint Paul Avenue
//  Opelousas, LA  70570                   info@tee-boy.com
//
//--------------------------------------------------------------------------------------------------

#import <Foundation/Foundation.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_5
@interface TBUpdateController : NSObject <NSURLConnectionDelegate>
#else
@interface TBUpdateController : NSObject
#endif
{
	id delegate;
	NSURLConnection *connection;
	NSMutableData *dataBuffer;
	NSString *version;
	NSString *build;
	NSString *url;
	NSString *productName;
}

@property (assign) id delegate;
@property (retain) NSURLConnection *connection;
@property (retain) NSMutableData *dataBuffer;
@property (retain) NSString *version;
@property (retain) NSString *build;
@property (retain) NSString *url;
@property (retain) NSString *productName;

+ (void)checkServerVersion:(id)sender;

@end
