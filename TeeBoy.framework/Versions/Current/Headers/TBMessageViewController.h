//
//  TBMessageViewController.h
//  WeatherSnoop
//
//  Created by Boisy Pitre on 2/25/13.
//  Copyright (c) 2013 Boisy Pitre. All rights reserved.
//

@interface TBMessageViewController : NSViewController
{
	IBOutlet NSTextField *messageField;
}

@property (assign) IBOutlet NSTextField *messageField;

- (void)centerOnView:(NSView *)hostView withMessage:(NSString *)message;

@end
