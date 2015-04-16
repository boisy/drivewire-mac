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

#define	TeeBoyErrorDomain @"com.tee-boy.TeeBoy.ErrorDomain"

#define	TBErrorSerialPortAlreadyOpen		-10
#define TBErrorSerialPortFailedToOpen		-11
#define	TBErrorSerialPortNonExistent		-12
#define	TBErrorInvalidAddress				-20
#define	TBErrorMalformedURL					-21
#define	TBErrorFailedToConnect				-22
#define	TBErrorBadStationID                 -23
#define	TBErrorNoAddressSpecified			-24
#define	TBErrorFileDoesntExist              -25

@interface NSError (TeeBoy)

+ (NSError *)serialPortFailedToOpen;
+ (NSError *)serialPortAlreadyOpen;
+ (NSError *)serialPortNonExistent;
+ (NSError *)malformedURL;
+ (NSError *)invalidAddress;
+ (NSError *)failedToConnect;
+ (NSError *)badStationID;
+ (NSError *)noAddressSpecified;
+ (NSError *)fileDoesntExist;

@end
