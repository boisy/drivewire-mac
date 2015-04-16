//
//  TBLicenseKit.h
//  WeatherSnoop
//
//  Created by Boisy Pitre on 11/28/11.
//  Copyright 2011 Tee-Boy. All rights reserved.
//

#import <TeeBoy/QHTTPOperation.h>


@interface TBLicenseKit : NSObject <QHTTPOperationDelegate>
{
	NSString *licenseFolder;

	NSString *licenseExtension;
	NSTimer	__unsafe_unretained	*demoTimer;
	BOOL        licensedAsMAS;
	NSDictionary *dictionary;

	NSUInteger	demoMinutes;
}

// License dictionary strings
#define kLicenseName				@"Name"					// the name of the licensee
#define kLicenseEmail				@"Email"				// the emaill address of the licensee
#define kLicenseItemNumber			@"ItemNumber"			// the item number for the product (used to designate different tiers of features)
#define kLicenseVendor				@"Vendor"				// the vendor who vended the license
#define kLicenseProductIdentifer    @"Product"				// the product identifier
#define kLicensePurchaseDate		@"PurchaseDate"			// the date the product was purchased
#define kLicenseProductVersion      @"ProductVersion"		// the version of the product purchased
#define kLicenseExpirationDate      @"ExpirationDate"		// the expiration date of the license

@property (retain) NSString *licenseFolder;
@property (retain) NSDictionary *dictionary;
@property (retain) NSString *licenseExtension;
@property (assign) NSUInteger demoMinutes;

- (BOOL)verifyRightToRunWithMASReceipt;
- (BOOL)verifyRightToRunWithKey:(NSString *)key;
- (void)runAsDemoForMinutes:(NSUInteger)minutes;

- (BOOL)application:(NSApplication *)theApplication openLicenseFile:(NSString *)filename usingKey:(NSString *)key showVerification:(BOOL)show;

- (NSString *)licensePath;
- (NSString *)licenseString;

- (NSString *)itemNumber;

@end
