//
//  VirtualScreenView.h
//  DriveWire
//
//  Created by Boisy Pitre on 4/17/15.
//
//

#import <Cocoa/Cocoa.h>

@interface VirtualScreenCharacter : NSObject

@property (assign) u_char character;
@property (strong) NSColor *foregroundColor;
@property (strong) NSColor *backgroundColor;

- (id)init;

@end

@interface VirtualScreenView : NSView

@property (assign) NSUInteger number;
@property (assign) BOOL shouldClose;
@property (strong) NSColor *backgroundColor;
@property (strong) NSColor *cursorColor;
@property (strong) NSColor *fontColor;
@property (assign) NSPoint nextCharacterPosition;
@property (assign) NSSize screenSize;
@property (strong) NSMutableArray *screen;
//@property (strong) NSMutableData *screenBuffer;
@property (assign) SEL characterProcessor;
@property (assign) u_char nextByte;
@property (assign) NSUInteger waitCounter;
@property (strong) NSMutableData *incomingBuffer;

- (void)putCharacter:(u_char)character;
- (NSUInteger)availableToRead;
- (u_char)getByte;

- (void)reset;

@end
