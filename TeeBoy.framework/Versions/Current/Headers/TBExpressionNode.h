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

#import <Foundation/Foundation.h>

typedef enum 
{    
	E_Constant,
	E_Variable,
	E_Function
} ExpType;

@interface TBExpressionNode : NSObject
{
    TBExpressionNode *left, *right, *parent;
	ExpType type;
	NSString *name;
    float value;
}

@property(retain) TBExpressionNode *left;
@property(retain) TBExpressionNode *right;
@property(retain) TBExpressionNode *parent;
@property ExpType type;
@property(retain) NSString *name;
@property float value;

- (void)visit;
- (void)makeRightParentOf:(TBExpressionNode *)node;
- (void)makeLeftChildOf:(TBExpressionNode *)parent;
- (void)makeRightChildOf:(TBExpressionNode *)parent;


@end
