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
 @header TBExpressionError.h
 @copyright Tee-Boy
 @abstract Expression Error Class
 @discussion TBExpressionError extends NSError and provides error information for expressions.
 @updated 2007-06-25
 */

#import <Foundation/Foundation.h>

/*!
 @enum	TBExpressionError
 @discussion An enumerated type describing an expression error.
 @constant	TBExpressionErrorNone					No error was detected for the current expression.
 @constant	TBExpressionErrorNAN					The result is not a number.
 @constant	TBExpressionErrorEmptyExpression		There is currently no expression set.
 @constant	TBExpressionErrorDivideByZero			Divide by zero error.
 @constant	TBExpressionErrorTooManyOpenParentheses	There are too many open parentheses in the expression.
 @constant	TBExpressionErrorTooManyClosingParentheses	There are too many closing parentheses in the expression.
 @constant	TBExpressionErrorUnknownOperator		An unknown operator was detected in the expression.
 @constant	TBExpressionErrorUnbalancedExpression	The expression is unbalanced.
 @constant	TBExpressionErrorUndefinedVariable		There is an undefined variable in the expression.
 @constant	TBExpressionErrorMalformedConstant		A malformed constant exists in the expression.
 @constant	TBExpressionErrorMalformedFunction		A malformed function exists in the expression.
 @constant	TBExpressionErrorInequality				The function evaluated to an inequality.
 @constant	TBExpressionErrorUnknownFunction		There is an unknown function in the expression.
 */
typedef enum
	{
		TBExpressionErrorNone = 0,
		TBExpressionErrorNAN,
		TBExpressionErrorINF,
		TBExpressionErrorEmptyExpression,
		TBExpressionErrorDivideByZero,
		TBExpressionErrorTooManyOpenParentheses,
		TBExpressionErrorTooManyClosingParentheses,
		TBExpressionErrorUnknownOperator,
		TBExpressionErrorUnbalancedExpression,
		TBExpressionErrorUndefinedVariable,
		TBExpressionErrorMalformedConstant,
		TBExpressionErrorMalformedFunction,
		TBExpressionErrorInequality,
		TBExpressionErrorUnknownFunction
	} TBExpressionErrorCode;

/*!
 @interface TBExpressionError
 @abstract Error object.
 @discussion The TBExpressionError extends NSError and provides error information for expressions.
 @updated 2008-07-13
 */
@interface TBExpressionError : NSError
{

}

@end
