/* LogView */

#import <Cocoa/Cocoa.h>

@interface LogView : NSView
{
    IBOutlet NSTextView *logTextView;
}

- (IBAction)clearLog:(id)sender;
- (IBAction)copyLog:(id)sender;

- (void)updateLog:(NSString *)logString;
- (void)update:(NSDictionary *)info;

@end
