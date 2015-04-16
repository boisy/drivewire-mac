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
#import <TeeBoy/TBSegView.h>
#import <TeeBoy/TBSegView.h>
#import <TeeBoy/TBLog.h>
#import <TeeBoy/TBTextView.h>

#define kAlarmTime				@"alarmTime"
#define kTwentyFourHourClock	@"twentyFourHourClock"
#define kAlarmActive			@"alarmActive"
#define kAlarmTime				@"alarmTime"
#define kAlarmSound				@"alarmSound"
#define kColorTheme				@"colorTheme"
#define kGlowEffect				@"glowEffect"

@protocol ExtendedNIBProtocol

- (void)awokeFromNib;

@end

@interface TBLEDClockViewController : NSViewController
{
	NSString *timeFormatWithColons;
	NSString *timeFormatWithoutColons;
	NSString *secondTimeFormatWithColons;
	NSString *secondTimeFormatWithoutColons;

	NSTimeInterval ticksPerSecond;
	NSTimeInterval currentTick;

	BOOL twentyFourHourClock;
	BOOL alarmActive;
	int alarmSound;
	BOOL glowEffect;
	
	NSTimer *alarm;
	
	BOOL alarmIsFiring;
	unsigned int soundCounter;
	
	NSArray *sounds;
	
	NSSize regularSize;
	
	NSTimer *timer;

	int colorTheme;

	NSColor *backgroundColor;
	
	id delegate;
	
	BOOL allowContextMenu;
	
@public
	IBOutlet TBSegView *hoursAndMinutes;
	IBOutlet TBSegView *hoursMinutesAndSeconds;
	IBOutlet TBTextView *amPmView;
	IBOutlet TBTextView *alarmView;
}

@property(retain) id delegate;
@property BOOL twentyFourHourClock;
@property int colorTheme;
@property BOOL allowContextMenu;

- (id)initWithDelegate:(id)_delegate;

- (void)setGlowEffect:(BOOL)onOrOff;
- (void)setColorTheme:(int)theme;
- (NSColor *)backgroundColor;
- (void)setBackgroundColor:(NSColor *)newBackgroundColor;

- (void)cancelAlarm;
- (void)playAlarmSound;

@end
