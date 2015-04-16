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
 @header TBExpression.h
 @copyright Tee-Boy
 @abstract A mathematical expression parser class.
 @discussion TBExpression parses mathematical expressions and provides results.
 @updated 2007-06-25
 */

#import <Foundation/Foundation.h>
#import "TBExpressionNode.h"
#import "TBExpressionError.h"

/*!
 @class TBExpression
 @abstract Parses and evaluates mathematical expressions.
 @discussion The TBExpression class provides the necessary intelligence to parse and process complex mathematical expressions.
 @updated 2008-07-13
 */
@interface TBExpression : NSObject
{
	void				*_private_data;
}

/*!
 @method setDelegate
 @abstract Sets the delegate.
 @param value The id of the delegate.
 */
- (void)setDelegate:(id)value;

/*!
 @method delegate
 @abstract Returns the delegate.
 @result The currently assigned delegate.
 */
- (id)delegate;

/*!
 @method setExpression:error:
 @abstract Sets mathematical expression to be evaluated.
 @param value The mathematical expression to be evaluated.
 @param error Error if any
 */
- (void)setExpression:(NSString *)value error:(TBExpressionError **)error;

/*!
 @method expression
 @abstract Returns a copy of the current mathematical expression string.
 @result A copy of the current mathematical expression string.
 */
- (NSString *)expression;

/*!
 @method setVariableDictionary
 @abstract Sets the variable dictionary.
 @param value The variable dictionary to use.
 */
- (void)setVariableDictionary:(NSMutableDictionary *)value;

/*!
 @method variableDictionary
 @abstract Returns a pointer to the variable dictionary.
 @result A pointer to the variable dictionary.
 */
- (NSMutableDictionary *)variableDictionary;

/*!
 @method evaluate:
 @abstract Evaluates the internal expression and returns the result.
 @param error Returned error (nil if no error)
 @result Result of the expession evaluation (valid if error is nil).
 */
- (float)evaluate:(TBExpressionError **)error;

@end

/*!
 @protocol TBExpressionDelegate
 @abstract Protocol for communicating expressions.
 @discussion
 @updated 2008-07-13
 */
@interface NSObject (TBExpressionDelegate)

/*!
 @method expressionDidChange
 @abstract A delegate method which notifies the delegate that the expression has been modified
 @param expression The TBExpression object whose expression has been changed.
 */
- (void)expressionDidChange:(id)expression;

- (NSString *)localizedDescription;

@end
