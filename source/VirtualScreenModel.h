//
//  VirtualScreenModel.h
//  DriveWire MacServer
//
//  Created by Boisy Pitre on 4/17/15.
//
//

@interface VirtualScreenModel : NSObject

@property (assign) NSSize size; // size of screen in characters

- (id)initWithScreenSize:(NSSize)screenSize;

- (void)putCharacter:(u_char)character atPosition:(NSPoint)position;

@end
