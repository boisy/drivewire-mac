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

@interface TBSysInfo : NSObject 
{
	SInt32 _versionMajor, _versionMinor, _versionBugFix;
}

@property (readonly) SInt32 versionMajor;
@property (readonly) SInt32 versionMinor;
@property (readonly) SInt32 versionBugFix;

+ (TBSysInfo *)sharedObject;

+ (BOOL)usingCheetah;
+ (BOOL)usingPuma;
+ (BOOL)usingJaguar;
+ (BOOL)usingPanther;
+ (BOOL)usingTiger;
+ (BOOL)usingLeopard;
+ (BOOL)usingSnowLeopard;
+ (BOOL)usingLion;
+ (BOOL)usingMountainLion;
+ (BOOL)usingMavericks;
+ (BOOL)usingYosemite;

- (NSString *)osxVersionString;
- (NSString *)osxVersionName;

- (NSUInteger)physicalRAMSize;
- (NSUInteger)clockSpeed;
- (NSUInteger)numberOfCores;
- (NSString *)machineName;
- (NSString *)CPUName;

@end
