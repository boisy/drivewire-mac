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

#import <TeeBoy/TBView.h>

@interface TBTextView : TBView
{
	NSString *text;
	NSColor  *textColor;
	NSShadow *shadow;
	float	blurRadius;
	BOOL	glow;
}

@property(retain) NSString *text;
@property BOOL glow;

- (void)setTextColor:(NSColor *)value;

@end
