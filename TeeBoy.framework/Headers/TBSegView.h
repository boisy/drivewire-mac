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

/*!
	@header TBSegView.h
	@copyright Tee-Boy
	@abstract 7-Segment Display Class
	@discussion TBSegView provides a 7-segment display along with controls for color and content.
	@updated 2007-06-25
 */

#import <TeeBoy/TBView.h>

#define	DISPLAY_CHAR_WIDTH			33
#define	DISPLAY_CHAR_HEIGHT			53
#define	DISPLAY_DIGIT_WIDTH			DISPLAY_CHAR_WIDTH
#define	DISPLAY_DIGIT_HEIGHT		DISPLAY_CHAR_HEIGHT
#define	DISPLAY_DASH_WIDTH			DISPLAY_CHAR_WIDTH
#define	DISPLAY_DASH_HEIGHT			DISPLAY_CHAR_HEIGHT
#define	DISPLAY_SPACE_WIDTH			DISPLAY_CHAR_WIDTH
#define	DISPLAY_SPACE_HEIGHT		DISPLAY_CHAR_HEIGHT
#define	DISPLAY_COLON_WIDTH			DISPLAY_CHAR_WIDTH / 3
#define	DISPLAY_COLON_HEIGHT		DISPLAY_CHAR_HEIGHT
#define	DISPLAY_PERIOD_WIDTH		DISPLAY_CHAR_WIDTH / 3
#define	DISPLAY_PERIOD_HEIGHT		DISPLAY_CHAR_HEIGHT
#define	DISPLAY_BLANK_COLON_WIDTH	DISPLAY_CHAR_WIDTH / 3
#define	DISPLAY_BLANK_COLON_HEIGHT	DISPLAY_CHAR_HEIGHT
#define	DISPLAY_BLANK_PERIOD_WIDTH	DISPLAY_CHAR_WIDTH / 3
#define	DISPLAY_BLANK_PERIOD_HEIGHT	DISPLAY_CHAR_HEIGHT

//#define	DISPLAY_CHAR_WIDTH_PADDING	((DISPLAY_CHAR_WIDTH / 4) * 2)
	// Padding between characters

#define	DISPLAY_CHAR_HEIGHT_PADDING	(((DISPLAY_CHAR_HEIGHT + 1) / 7) + 1)
	// Padding between characters

#define	DISPLAY_COMPUTE_WIDTH(nChars, wMul)	\
	((((DISPLAY_CHAR_WIDTH + DISPLAY_CHAR_WIDTH_PADDING) * wMul) * nChars) \
	+ (DISPLAY_CHAR_WIDTH_PADDING * DISPLAY_WIDTH_MULTIPLIER))
#define	DISPLAY_COMPUTE_HEIGHT(wMul)	\
	(((DISPLAY_CHAR_HEIGHT * wMul) + DISPLAY_CHAR_HEIGHT_PADDING) \
	+ (DISPLAY_CHAR_HEIGHT_PADDING * DISPLAY_HEIGHT_MULTIPLIER))

#define	DISPLAY_CREATE_RECT(rect, x, y, numChars, widthMul, heightMul) \
		rect.left = x; \
		rect.top = y; \
		rect.right = rect.left + DISPLAY_COMPUTE_WIDTH(numChars, widthMul) - 1; \
		rect.bottom = rect.top + DISPLAY_COMPUTE_HEIGHT(heightMul) - 1;	


typedef enum
{
	TB_COLORTHEME_RED, TB_COLORTHEME_GREEN,TB_COLORTHEME_BLUE,
	TB_COLORTHEME_YELLOW, TB_COLORTHEME_ORANGE, TB_COLORTHEME_MAGENTA,
	TB_COLORTHEME_PURPLE, TB_COLORTHEME_GRAY
} TBColorTheme;

/*!
	@class TBSegView
	@discussion This class encapsulates the Virtual Display component
*/
@interface TBSegView : TBView
{
@private
	// **** PRIVATE VARIABLES ****
	Boolean			powerState;		// Is it on (true) or off (false)?
	NSString		*contents;
	int				contentsWidth;	// width of content in pixels
	int				characterWidth;	// width of content in characters
	NSColor			*backOn;
	NSColor			*backOff;
	NSColor			*segmentOn;
	NSColor			*segmentDim;
	TBColorTheme	colorTheme;

	float			scaleX, scaleY;
	float			shearX, shearY;
	float			wm;
	float			hm;
	Boolean			stroke, freeScale, glow;
	float			strokeWidth;
		
	// Padding variables
	int				widthPadding;
//	int				heightPadding;
	
	NSPoint			nextDrawPoint;
	NSBezierPath	*segPath;
	NSArray			*colorThemeArray;
#ifndef IOS
	NSShadow		*shadow;
#endif
	float			blurRadius;
};

#pragma mark Init/Deinit Methods
- (id)initWithCoder:(NSCoder *)decoder;
- (void)encodeWithCoder:(NSCoder *)coder;

#pragma mark Glow methods

/*!
	@method setGlow
	@abstract Sets the display glow state.
 */
- (void)setGlow:(BOOL)state;


/*!
	@method glow
	@abstract Returns the display glow state.
	@result The state of the glow is returned.
 */
- (BOOL)glow;


#pragma mark Color methods

/*!
	@method colorTheme
	@abstract Gets the display's color theme.
	@result The current color theme is returned.
 */
- (TBColorTheme)colorTheme;


/*!
	@method setColorTheme
	@abstract Sets the display's color theme.
	@param color The color theme to set.
 */
- (void)setColorTheme:(TBColorTheme)theme;


/*!
	@method setBackgroundOnColor
	@abstract Sets the display view's "ON" background color
	@param color The color to set.
 */
- (void)setBackgroundOnColor:(NSColor *)color;


/*!
	@method backgroundOnColor
	@abstract Returns the display view's "ON" background color.
	@result The current color is returned.
 */
- (NSColor *)backgroundOnColor;


/*!
	@method setBackgroundOffColor
	@abstract Sets the display view's "OFF" background color
	@param color The color to set.
 */
- (void)setBackgroundOffColor:(NSColor *)color;


/*!
	@method backgroundOffColor
	@abstract Returns the display view's "OFF" background color.
	@result The current color is returned.
*/
- (NSColor *)backgroundOffColor;


/*!
	@method setSegmentOnColor
	@abstract Sets the display view's "ON" segment color
	@param color The color to set.
 */
- (void)setSegmentOnColor:(NSColor *)color;


/*!
	@method segmentOnColor
	@abstract Returns the display view's "ON" sgment color.
	@result The current color is returned.
 */
- (NSColor *)segmentOnColor;


/*!
	@method setSegmentDimColor
	@abstract Sets the display view's "DIM" segment color
	@param color The color to set.
 */
- (void)setSegmentDimColor:(NSColor *)color;


/*!
	@method backgroundOnColor
	@abstract Returns the display view's "ON" background color.
	@result The current color is returned.
 */
- (NSColor *)segmentDimColor;


#pragma mark Scaling methods

/*
	@method setCharacterWidth
	@abstract Sets the width in characters.
	@param value The width in characters.
 */
- (void)setCharacterWidth:(BOOL)value;


/*
	@method characterWidth
	@abstract Returns the width in characters of the view.
	@result Returns the width in characters.
 */
- (BOOL)characeterWidth;


/*
	@method setFreeScale
	@abstract Sets the "scale to view" flag.
	@param value If YES, then the contents will be drawn to scale within the
	frame; otherwise, the contents will be drawn with respect to the X/Y
	scaling values.
 */
- (void)setFreeScale:(BOOL)value;


/*
	@method freeScale
	@abstract Returns the "scale to view" flag.
	@result Returns YES if scaling is set to the view; otherwise, NO.
 */
- (BOOL)freeScale;


/*!
	@method setScaleX
	@abstract Sets the width scale of the display.
	@param scaleValue The value to scale the width.
 */
- (void)setScaleX:(float)scaleValue;

	
/*!
	@method setScaleY
	@abstract Sets the height scale of the display.
	@param scaleValue The value to scale the height.
 */
- (void)setScaleY:(float)scaleValue;


/*!
	@method scaleX
	@abstract Returns the width scale of the display.
	@result The width scale of the display.
 */
- (float)scaleX;


/*!
	@method scaleY
	@abstract Returns the height scale of the display.
	@result The height scale of the display.
 */
- (float)scaleY;


/*!
	@method setShearX
	@abstract Sets the width shear of the display.
	@param shearValue The value to shear the width.
 */
- (void)setShearX:(float)shearValue;

	
/*!
	@method setShearY
	@abstract Sets the height shear of the display.
	@param shearValue The value to shear the height.
 */
- (void)setShearY:(float)shearValue;


/*!
	@method shearX
	@abstract Returns the width shear of the display.
	@result The width shear of the display.
 */
- (float)shearX;


/*!
	@method shearX
	@abstract Returns the height shear of the display.
	@result The height shear of the display.
 */
- (float)shearY;


/*!
	@method stroke
	@abstract Returns the stroke flag.
	@result The value of the stroke flag.
 */
- (BOOL)stroke;


/*!
	@method setStroke
	@abstract Sets the stroke flag.
	@param value If YES, then the characters will be stroked; otherwise they
	will be filled.
 */
- (void)setStroke:(BOOL)value;


/*!
	@method strokeWidth
	@abstract Returns the stroke width.
	@result The current stroke width.
 */
- (float)strokeWidth;


/*!
	@method setStrokeWidth
	@abstract Sets the stroke width.
	@param value Width to set.
 */
- (void)setStrokeWidth:(float)value;


/*!
	@method power
	@abstract Returns the power status of the display.
	@result The state of the display (TRUE = ON, FALSE = OFF)
 */
- (BOOL)power;

	
/*!
	@method setPower
	@abstract Sets the power state of the display.
	@param state The power state to set the display to.
 */
- (void)setPower:(BOOL)state;
	

/*!
	@method setValue
	@abstract Sets the display's value.
	@param value The value that will appear in the display.
 */
- (void)setValue:(id)value;		// Set Value


/*!
	@method value
	@abstract Returns the display's value.
	@result The value of the display.
 */
- (NSString *)value;							// Get Value

@end
