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

#import <Cocoa/Cocoa.h>

@interface TBGreenBarTextView : NSTextView
{
	NSColor *lineColor;
	NSColor *alternateLineColor;
	NSImage *image;
	BOOL drawsLinesAndImage;
}

- (void)setLineColor:(NSColor *)color;
- (void)setAlternateLineColor:(NSColor *)color;
- (NSColor *)lineColor;
- (NSColor *)alternateLineColor;
- (void)setImage:(NSImage *)newImage;
- (NSImage *)image;
- (void)setDrawsLinesAndImage:(BOOL)flag;
- (BOOL)drawsLinesAndImage;

@end
