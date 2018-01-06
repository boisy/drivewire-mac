//
//  VirtualScreenView.m
//  DriveWire
//
//  Created by Boisy Pitre on 4/17/15.
//
//

#import "VirtualScreenView.h"

@implementation VirtualScreenCharacter

- (id)initWithCharacter:(u_char)character;
{
    if (self = [super init])
    {
        self.character = character;
        self.foregroundColor = [NSColor blackColor];
        self.backgroundColor = [NSColor greenColor];
    }
    
    return self;
}

- (id)init;
{
    return [self initWithCharacter:0];
}

@end

@implementation VirtualScreenView

#define pixelXPosition(x) ((x % (int)self.screenSize.width) * charSize.width)
#define pixelYPosition(y) (self.frame.size.height - charSize.height - (row * charSize.height))

- (void)clearDisplay;
{
//    self.screenBuffer = [NSMutableData dataWithLength:self.screenSize.width * self.screenSize.height];
    self.screen = [NSMutableArray arrayWithCapacity:self.screenSize.width * self.screenSize.height];
    for (int i = 0; i < self.screenSize.width * self.screenSize.height; i++)
    {
        VirtualScreenCharacter *c = [VirtualScreenCharacter new];
        [self.screen addObject:c];
    }
    
    self.nextCharacterPosition = NSZeroPoint;
    [self setNeedsDisplay:YES];
}

- (void)reset;
{
    self.screenSize = NSMakeSize(80, 24);
    self.backgroundColor = [NSColor greenColor];
    self.cursorColor = [NSColor blackColor];
    self.fontColor = [NSColor blackColor];
    self.characterProcessor = @selector(nonEscapeCharacter);
    self.incomingBuffer = [NSMutableData new];
    [self clearDisplay];
}

- (id)initWithFrame:(NSRect)frame;
{
    if (self = [super initWithFrame:frame])
    {
        [self reset];
    }
    
    return self;
}

- (id)initWithCoder:(NSCoder *)decoder;
{
    if (self = [super initWithCoder:decoder])
    {
        [self reset];
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {

    // draw background color
    NSSize charSize = NSMakeSize(self.frame.size.width / self.screenSize.width, self.frame.size.height / self.screenSize.height);

//    char *bytes = (char *)[self.screenBuffer bytes];
//    for (int i = 0; i < [self.screenBuffer length]; i++)
    for (int i = 0; i < self.screenSize.width * self.screenSize.height; i++)
    {
        VirtualScreenCharacter *c = [self.screen objectAtIndex:i];
        if (i == 0)
        {
            // clear screen
            [c.backgroundColor set];
            NSRectFill(dirtyRect);
        }
        [c.backgroundColor setFill];
        char ch = c.character;
        if (ch != 0x00)
        {
            NSUInteger column = i % (int)self.screenSize.width;
            NSUInteger row = i / self.screenSize.width;
            NSRect rectToDraw = NSMakeRect(pixelXPosition(column), pixelYPosition(row), charSize.width, charSize.height);
            
            NSRectFill(rectToDraw);

            NSDictionary *attributes = @{NSFontAttributeName : [NSFont fontWithName:@"Courier New" size:10.0],
                                         NSForegroundColorAttributeName : c.foregroundColor,
                                         NSBackgroundColorAttributeName : c.backgroundColor,
                                         NSBaselineOffsetAttributeName : @1.0
                                         };
            [[NSString stringWithFormat:@"%c", ch] drawInRect:rectToDraw withAttributes:attributes];
        }
    }
    
    // draw cursor
    NSUInteger column = self.nextCharacterPosition.x;
    NSUInteger row = self.nextCharacterPosition.y;
    NSRect rectToDraw = NSMakeRect(pixelXPosition(column), pixelYPosition(row), charSize.width, charSize.height);
    [self.cursorColor setFill];
    NSRectFill(rectToDraw);
    [super drawRect:dirtyRect];
}

- (void)incrementYPosition;
{
    CGFloat x = 0.0;
    CGFloat y = self.nextCharacterPosition.y;

    // handle CR
    y++;
    if (y >= self.screenSize.height)
    {
        y = self.screenSize.height - 1;
        
        // scroll time
        // copy everything up
#if 0
        char *bytes = (char *)[self.screenBuffer bytes];
        int lineWidth = self.screenSize.width;
        char *secondLine = &bytes[lineWidth];
        int bytesToCopy = self.screenSize.width * (self.screenSize.height - 1);
        char *lastLine = &bytes[bytesToCopy];
        memcpy(bytes, secondLine, bytesToCopy);
        memset(lastLine, 0, self.screenSize.width);
#endif
        
    }
    self.nextCharacterPosition = NSMakePoint(x, y);
}

- (void)incrementXPosition;
{
    CGFloat x = self.nextCharacterPosition.x;

    x++;
    if (x >= self.screenSize.width)
    {
        x = 0;
        self.nextCharacterPosition = NSMakePoint(x, self.nextCharacterPosition.y);
        [self incrementYPosition];
    }
    else
    {
        self.nextCharacterPosition = NSMakePoint(x, self.nextCharacterPosition.y);
    }
}

- (void)putCharacter:(u_char)character;
{
    self.nextByte = character;
    [self performSelector:self.characterProcessor withObject:nil];
}

- (void)nonEscapeCharacter;
{
    if (self.nextByte >= 0x20)
    {
        NSUInteger location = self.nextCharacterPosition.y * self.screenSize.width + self.nextCharacterPosition.x;
        VirtualScreenCharacter *ch = [self.screen objectAtIndex:location];
        ch.foregroundColor = self.fontColor;
        ch.backgroundColor = self.backgroundColor;
        ch.character = self.nextByte;
        [self incrementXPosition];
        [self setNeedsDisplay:YES];
    }
    else
    {
        switch (self.nextByte)
        {
            case 0x0C:
                [self clearDisplay];
                break;
                
            case 0x0D:
                [self incrementYPosition];
                [self setNeedsDisplay:YES];
                break;
                
            case 0x1B:
                // start processing escape codes
                self.characterProcessor = @selector(escape1Character);
                break;

            case 0x0A:
                break; // ignore

            default:
                break;
        }
    }
}

- (void)escape1Character;
{
    // character following 1b
    switch (self.nextByte)
    {
        case 0x32:
            self.characterProcessor = @selector(screenForegroundColor);
            break;
            
        case 0x33:
            self.characterProcessor = @selector(screenBackgroundColor);
            break;
            
        case 0x34:
            self.characterProcessor = @selector(screenBorderColor);
            break;
            
        default:
            self.characterProcessor = @selector(nonEscapeCharacter);
            break;
    }
}

- (NSColor *)colorForCode:(NSUInteger)code;
{
    NSColor *result = nil;
    
    switch (self.nextByte & 0x07)
    {
        case 0x00:
            result = [NSColor whiteColor];
            break;
            
        case 0x01:
            result = [NSColor blueColor];
            break;
            
        case 0x02:
            result = [NSColor blackColor];
            break;
            
        case 0x03:
            result = [NSColor greenColor];
            break;
            
        case 0x04:
            result = [NSColor redColor];
            break;
            
        case 0x05:
            result = [NSColor yellowColor];
            break;
            
        case 0x06:
            result = [NSColor magentaColor];
            break;
            
        case 0x07:
            result = [NSColor cyanColor];
            break;
            
        default:
            result = [NSColor blackColor];
    }
    
    return result;
}

- (void)screenForegroundColor;
{
    self.fontColor = [self colorForCode:self.nextByte];
    [self setNeedsDisplay:YES];
    self.characterProcessor = @selector(nonEscapeCharacter);
}

- (void)screenBackgroundColor;
{
    self.backgroundColor = [self colorForCode:self.nextByte];
    [self setNeedsDisplay:YES];
    self.characterProcessor = @selector(nonEscapeCharacter);
}

- (void)screenBorderColor;
{
    self.characterProcessor = @selector(nonEscapeCharacter);
}

- (BOOL)acceptsFirstResponder;
{
    return YES;
}

- (void)keyDown:(NSEvent *)theEvent
{
    NSString  *characters = [theEvent characters];
    char  c = [characters characterAtIndex: 0];
    [self.incomingBuffer appendBytes:&c length:1];
}

- (NSUInteger)availableToRead;
{
//    return [self.incomingBuffer length];
    return [self.incomingBuffer length];
}

- (u_char)getByte;
{
    u_char result = 0;
    
#if 0
    if ([self hasData])
    {
        result = *(u_char *)[self.incomingBuffer bytes];
        [self.incomingBuffer replaceBytesInRange:NSMakeRange(0, 1) withBytes:nil length:0];
        [[NSNotificationCenter defaultCenter] postNotificationName:kVirtualChannelDataReceivedNotification
                                                            object:self.model
                                                          userInfo:@{@"channel" : self}];
    }
    
    return result;
#endif
    result = *(u_char *)[self.incomingBuffer bytes];
    [self.incomingBuffer replaceBytesInRange:NSMakeRange(0, 1) withBytes:nil length:0];
    
    return result;
}

@end

