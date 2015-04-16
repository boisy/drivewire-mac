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
 @header TBLog.h
 @copyright Tee-Boy
 @abstract A flexible logging class.
 @discussion Logging is a critical component in applications, especially when tracking down issues or
 trying to trace behavior. The TBLog class was designed to provide a powerful set of logging capabilities
 in an easy to use, simple package.
 @updated 2012-06-28
 */

#import <asl.h>

#define kTBLogNotification @"TBLogNotification"


/*!
 @typedef TBLogLevel
 @discussion The values in the enumeration mimics ASL log levels.
 */
typedef enum
{
    TBLogLevelEmergency = ASL_LEVEL_EMERG,
    TBLogLevelAlert = ASL_LEVEL_ALERT,
    TBLogLevelCritical = ASL_LEVEL_CRIT,
    TBLogLevelError = ASL_LEVEL_ERR,
    TBLogLevelWarning = ASL_LEVEL_WARNING,
    TBLogLevelNotice = ASL_LEVEL_NOTICE,
    TBLogLevelInfo = ASL_LEVEL_INFO,
    TBLogLevelDebug = ASL_LEVEL_DEBUG
} TBLogLevel;

#define TBLogFormat(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]

// Convenience macros
// Set the log level
#define  TBLogLevel(lvl)              [[TBLog sharedLog] setLogLevel:lvl]
// Turn standard error logging on to see log messages in your Xcode console window
#define  TBLogStdErr(boolValue)       [[TBLog sharedLog] setLogStandardError:boolValue]

#define TBLogEmergency(format, ...)   [[TBLog sharedLog] logLevel:TBLogLevelEmergency message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]
#define TBLogAlert(format, ...)       [[TBLog sharedLog] logLevel:TBLogLevelAlert message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]
#define TBLogCritical(format, ...)    [[TBLog sharedLog] logLevel:TBLogLevelCritical message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]
#define TBLogError(format, ...)       [[TBLog sharedLog] logLevel:TBLogLevelError message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]
#define TBLogWarning(format, ...)     [[TBLog sharedLog] logLevel:TBLogLevelWarning message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]
#define TBLogNotice(format, ...)      [[TBLog sharedLog] logLevel:TBLogLevelNotice message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]
#define TBLogInfo(format, ...)        [[TBLog sharedLog] logLevel:TBLogLevelInfo message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]
#define TBLogDebug(format, ...)       [[TBLog sharedLog] logLevel:TBLogLevelDebug message:[NSString stringWithFormat:(format), ##__VA_ARGS__]]

#define kLogState               @"logState"
#define kLogLevel               @"logLevel"
#define kLogStandardError       @"logStandardError"
#define kDebugProfile           @"DebugProfile"
#define kNumberOfDaysToKeepLogs @"logDaysToKeep"

/*!
 @class TBLog
 @discussion This is a full-featured logging class.
 */
@interface TBLog : NSObject
{
    TBLogLevel      logLevel;
    BOOL            logState;
    NSString        *bundleName;
    NSString        *bundleID;
    NSDictionary    *logTags;
    FILE            *_logFD;
    NSString        *logDirectory;
    NSString        *logFilePath;
}

/*!
 @method sharedLog
 @discussion The singleton object is returned from this class method.
 */

+ (TBLog *)sharedLog;

/*!
 @method startNewLog
 @discussion When called, the current log is closed and a new log file is created.
 All subsequent logging goes into the new log file.
*/
- (void)startNewLog;

- (NSArray *)logLevelNameArray;

- (id)initWithProfile:(NSInteger)profile logDirectory:(NSString *)theLogDirectory;
- (id)initWithLogDirectory:(NSString *)theLogFolder;

/*!
 @method dumpFrames
 @discussion This method dumps the current stack frame.
 */
- (void)dumpFrames;

/*!
 @method logLevel:message:
 @discussion Sends a message to the logging system.
 @param level The log level to send the message as
 @param message The message to send
 */
- (void)logLevel:(TBLogLevel)level message:(NSString *)message;

/// \brief Send a message to the logging system (backward compatible method)
/// \param level The log level to send the message as
/// \param message The message to send
- (void)log:(NSString *)message level:(TBLogLevel)level;

/*!
 @method logLevel:message:info:
 @discussion Sends a message to the logging system.
 @param level The log level to send the message as
 @param message The message to send
 @param msgInfo Name value pairs to be associated with the logged message
 */
- (void)logLevel:(TBLogLevel)level message:(NSString *)message info:(NSDictionary *)msgInfo;

/*!
 @method logLevel:message:uti:attachmentName:attachment:
 @discussion Sends a message to the logging system along with an attachment.
 @param level The log level to send the message as
 @param message The message to send
 @param uti The uniform type identifier to send
 @param attachmentName The name of the file that the attachment will be saved to
 @param attachment The attachment data
 */
- (void)logLevel:(TBLogLevel)level message:(NSString *)message uti:(NSString *)uti attachmentName:(NSString *)attachmentName attachment:(NSData *)attachment;

/*!
 @method logLevel:message:uti:url:
 @discussion Sends a message to the logging system along with a URL.
 @param level The log level to send the message as
 @param message The message to send
 @param uti The uniform type identifier to send
 @param url The URL to send
 */
- (void)logLevel:(TBLogLevel)level message:(NSString *)message uti:(NSString *)uti url:(NSString *)url;

/*!
 @method setLogLevelFromString:
 @discussion Set the log level using a string.
 @param level The log level string to set the logging system to
 */
- (void)setLogLevelFromString:(NSString *)level;

/*!
 @method setLogLevelFromString:
 @discussion Set the log level.
 @param level The log level to set the logging system to
 */
- (void)setLogLevel:(TBLogLevel)level;

- (BOOL)logStandardError;

/*!
 @method setLogStandardError:
 @discussion If set to TRUE, then logging will also go to the standard error channel. If set to FALSE, no logging
 happens on that channel.
 @param value The boolean value to set standard error logging
 */
- (void)setLogStandardError:(BOOL)value;

/*!
 @method start
 @discussion When called, this method starts the logger.
 */
- (void)start;

/*!
 @method stop
 @discussion When called, this method stops the logger.
 */
- (void)stop;

/*!
 @method loadTagsForProfile:level:
 @discussion This method establishes a new set of filtering hashTags.
 */
- (void)loadTagsForProfile:(NSInteger)profile level:(TBLogLevel)level;

/*!
 @method sweepLogs
 @discussion Sweeps logs older than kNumberOfDaysToKeepLogs days.
 */
- (void)sweepLogs;

- (void)showInConsole;

@end



// TBLog Macros
#define TBSetProfile(num) {\
    [[TBLog sharedLog] loadTagsForProfile:num level:TBLogLevelDebug];\
}


#define TBCritical(format, ...)       {\
    NSString *_ddMsg = [NSString stringWithFormat:(format @" #%s"), ##__VA_ARGS__, MODULE_HASHTAG];\
    [[TBLog sharedLog] logLevel:TBLogLevelCritical message:_ddMsg];\
}

#define TBError(format, ...)       {\
    NSString *_ddMsg = [NSString stringWithFormat:(format @" #%s"), ##__VA_ARGS__, MODULE_HASHTAG];\
    [[TBLog sharedLog] logLevel:TBLogLevelError message:_ddMsg];\
}

#define TBNotice(format, ...)       {\
    NSString *_ddMsg = [NSString stringWithFormat:(format @" #%s"), ##__VA_ARGS__, MODULE_HASHTAG];\
    [[TBLog sharedLog] logLevel:TBLogLevelNotice message:_ddMsg];\
}

#define TBInfo(format, ...)       {\
    NSString *_ddMsg = [NSString stringWithFormat:(format @" #%s"), ##__VA_ARGS__, MODULE_HASHTAG];\
    [[TBLog sharedLog] logLevel:TBLogLevelInfo message:_ddMsg];\
}

#define TBDebug(format, ...)       {\
NSString *_ddMsg = [NSString stringWithFormat:(format @" #%s"), ##__VA_ARGS__, MODULE_HASHTAG];\
[[TBLog sharedLog] logLevel:TBLogLevelDebug message:_ddMsg];\
}

#ifndef NDEBUG
#define TBLog(format, ...)         {\
    NSString *_sourceFile = [[NSString stringWithUTF8String:__FILE__] lastPathComponent];\
    NSDictionary *_ddInfo = [NSDictionary dictionaryWithObjectsAndKeys:\
        [NSString stringWithFormat:@"%@:%d",_sourceFile,__LINE__], @"SourceFile",\
        [NSString stringWithUTF8String:__PRETTY_FUNCTION__], @"SourceMethod",\
        nil];\
    NSString *_ddMsg = [NSString stringWithFormat:(format @" #%s"), ##__VA_ARGS__, MODULE_HASHTAG];\
    [[TBLog sharedLog] logLevel:TBLogLevelDebug message:_ddMsg info:_ddInfo];\
}
#else
#define TBLog(format, ...) 
#endif

#define TBStackTrace() [[TBLog sharedLog] dumpFrames]

#define DDFatalException(ex, format, ...)       {\
    NSString *_ddMsg = [NSString stringWithFormat:(format @"%@ %@ #%s"), ##__VA_ARGS__, GTMStackTraceFromException(ex), MODULE_HASHTAG];\
    [[TBLog sharedLog] logLevel:TBLogLevelCritical message:_ddMsg];\
}
