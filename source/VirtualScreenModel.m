//
//  VirtualScreenModel.m
//  DriveWire
//
//  Created by Boisy Pitre on 4/17/15.
//
//

#import "VirtualScreenModel.h"

@interface VirtualScreenModel ()

@property (assign) u_char *screenBuffer;

@end

@implementation VirtualScreenModel

- (id)initWithScreenSize:(NSSize)screenSize;
{
    if (self = [super init])
    {
        self.size = screenSize;
        self.screenBuffer = calloc(screenSize.width, screenSize.height);
    }
    
    return self;
}

- (void)dealloc;
{
    free(self.screenBuffer);
}

- (void)putCharacter:(u_char)character atPosition:(NSPoint)position;
{
    NSUInteger location = position.y * self.size.width + position.x;
    
    self.screenBuffer[location] = character;
}

@end
