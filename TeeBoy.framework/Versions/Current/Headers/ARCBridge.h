//--------------------------------------------------------------------------------------------------
//
//  Copyright (c) 2010-2014 Tee-Boy
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
//  $Id$
//--------------------------------------------------------------------------------------------------

#if !defined(__clang__) || __clang_major__ < 3
#ifndef __bridge
#define __bridge
#endif

#ifndef __bridge_retain
#define __bridge_retain
#endif

#ifndef __bridge_retained
#define __bridge_retained
#endif

#ifndef __bridge_transfer
#define __bridge_transfer
#endif

#ifndef __autoreleasing
#define __autoreleasing
#endif

#ifndef __strong
#define __strong
#endif

#ifndef __unsafe_unretained
#define __unsafe_unretained
#endif

#ifndef __weak
#define __weak
#endif
#endif

#define SAFE_ARC_PROP_RETAIN retain
#define SAFE_ARC_RETAIN(x) ([(x) retain])
#define SAFE_ARC_RELEASE(x) ([(x) release])
#define SAFE_ARC_AUTORELEASE(x) ([(x) autorelease])
#define SAFE_ARC_BLOCK_COPY(x) (Block_copy(x))
#define SAFE_ARC_BLOCK_RELEASE(x) (Block_release(x))
#define SAFE_ARC_SUPER_DEALLOC(); ([super dealloc])
#define SAFE_ARC_AUTORELEASE_POOL_START() NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#define SAFE_ARC_AUTORELEASE_POOL_END() [pool drain];
#define SAFE_ARC_CFBRIDGINGRELEASE(x) x
#define NO_ARC
#if defined(__clang__)
#if __has_feature(objc_arc)
#undef SAFE_ARC_PROP_RETAIN
#undef SAFE_ARC_RETAIN
#undef SAFE_ARC_RELEASE
#undef SAFE_ARC_AUTORELEASE
#undef SAFE_ARC_BLOCK_COPY
#undef SAFE_ARC_BLOCK_RELEASE
#undef SAFE_ARC_SUPER_DEALLOC
#undef SAFE_ARC_AUTORELEASE_POOL_START
#undef SAFE_ARC_AUTORELEASE_POOL_END
#undef SAFE_ARC_CFBRIDGINGRELEASE

#define SAFE_ARC_PROP_RETAIN strong
#define SAFE_ARC_RETAIN(x) (x)
#define SAFE_ARC_RELEASE(x)
#define SAFE_ARC_AUTORELEASE(x) (x)
#define SAFE_ARC_BLOCK_COPY(x) (x)
#define SAFE_ARC_BLOCK_RELEASE(x)
#define SAFE_ARC_SUPER_DEALLOC();
#define SAFE_ARC_AUTORELEASE_POOL_START() @autoreleasepool {
#define SAFE_ARC_AUTORELEASE_POOL_END() }
#define SAFE_ARC_CFBRIDGINGRELEASE(x) CFBridgingRelease(x)
#undef NO_ARC
#endif
#endif
