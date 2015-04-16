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

@interface TBQueueImpl : NSObject
{
	NSMutableArray	*messages, *priorityMessages;
	NSConditionLock	*lock;	
	BOOL keepPunching;
}

typedef enum _TBQueueState
{
	EMPTY = 0,
	NOT_EMPTY = 1
} TBQueueState;

- (id)init;
- (void)enqueueMessage:(id)object target:(id)target selector:(SEL)selector;
- (void)enqueuePriorityMessage:(id)object target:(id)target selector:(SEL)selector;
- (id)dequeue;				// Blocks until there is an object to return
- (id)tryDequeue;			// Returns nil if the TBQueue is empty
- (void)dealloc;
- (void)cancel:(id)target;

@end

@interface TBQueue : NSObject
{
	TBQueueImpl		*q;
	NSThread		*consumerThread;
}

- (void)enqueueMessage:(id)object target:(id)target selector:(SEL)selector;
- (void)enqueuePriorityMessage:(id)object target:(id)target selector:(SEL)selector;
- (void)cancel:(id)target;

@end