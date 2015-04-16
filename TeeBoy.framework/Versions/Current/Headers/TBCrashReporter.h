//
//  TBCrashReporter.h
//  WeatherSnoop3_Xcode326
//
//  Created by boisy on 6/29/14.
//  Copyright 2014 Boisy Pitre. All rights reserved.
//

#import <TeeBoy/QHTTPOperation.h>

@interface TBCrashReporter : NSObject <QHTTPOperationDelegate>
{
	QHTTPOperation *operation;
}

@property (retain) QHTTPOperation *operation;

- (void)gatherCrashReportsForPrefix:(NSString *)prefix sendTo:(NSURL *)url fromPerson:(NSString *)name andEmail:(NSString *)email;

@end
