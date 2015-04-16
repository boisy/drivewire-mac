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
	@header TBRandom.h
	@copyright Tee-Boy
	@abstract Random number generator.
	@discussion TBRandom creates random numbers.
	@updated 2007-06-25
 */

/*!
	@interface TBRandom
	@abstract Random generator class.
	@discussion This class facilitates the generation of random numbers.
*/
@interface TBRandom : NSObject
{
	NSNumber *_min, *_max;
#ifdef KEEP_USED_ARRAY
	NSMutableArray *used;
#endif
}

/*!
	@method init
	@abstract Initializes a new instance of the class.
	@result The id of the newly created object.
 */
- (id)init;

/*!
	@method initWithRangeBetween:and:
	@abstract Initalizes a generator which will return a within a range.
	@param min The minimum value that the generator will return.
	@param max The maximum value that the generator will return.
	@result The id of the newly created object.
 */
- (id)initWithRangeBetween:(NSNumber *)min and:(NSNumber *)max;

- (NSNumber *)rangeMin;
- (NSNumber *)rangeMax;

/*!
 @method setRangeMin:andMax:
 @abstract Sets the minimum and maximum ends of the range.
 @param minValue The minimum value that the generator will return.
 @param maxValue The maximum value that the generator will return.
 */
- (void)setRangeMin:(NSNumber *)minValue andMax:(NSNumber *)maxValue;

/*!
	@method setRangeMin
	@abstract Sets the minimum end of the range.
	@param value The minimum value that the generator will return.
 */
- (void)setRangeMin:(NSNumber *)value;

/*!
	@method setRangeMax
	@abstract Sets the maximum end of the range.
	@param value The maximum value that the generator will return.
 */
- (void)setRangeMax:(NSNumber *)value;

/*!
	@method generate
	@abstract Generates a new random number
	@result The generated number.
 */
- (NSNumber *)generate;

@end
