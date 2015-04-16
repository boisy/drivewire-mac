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

#import <AppKit/AppKit.h>

@interface TBImageView : NSImageView
{
    NSImage *_image;
    NSColor *_bgColor;
    NSImageScaling _scaling;
}

- (void)setImage:(NSImage*)image;
- (void)setImageScaling:(NSImageScaling)newScaling;
- (void)setBackgroundColor:(NSColor*)color;
- (NSImage*)image;
- (NSColor*)backgroundColor;
- (NSImageScaling)imageScaling;

@end