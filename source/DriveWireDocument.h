/* DriveWireDocument */

#import <Cocoa/Cocoa.h>
#import "VirtualDriveJukeBoxView.h"
#import "DriveWireServerModel.h"
#import "PrinterWindowController.h"
#import "DebuggerWindowController.h"
#import "LogViewController.h"
#import "StatsViewController.h"

@interface DriveWireDocument : NSDocument <DriveWireDelegate>
{
    IBOutlet VirtualDriveJukeBoxView *driveView;
    IBOutlet NSPopUpButton *serialPortButton;
    IBOutlet NSPopUpButton *machineTypePopupButton;
    IBOutlet NSImageView *machineImageView;
	NSInteger lastPortSelected;
    NSWindowController *myWindowController;
}

@property (strong) DriveWireServerModel *dwModel;
@property (strong) TBLog *log;
@property (assign) IBOutlet DebuggerWindowController *debuggerWindowController;
@property (assign) IBOutlet PrinterWindowController *printerWindowController;

- (void)updateMemoryView:(NSDictionary *)info;
- (void)updateRegisterView:(NSDictionary *)info;
- (void)updatePrinterView:(NSDictionary *)info;

- (void)updateUIComponents;
- (IBAction)setCoCoType:(id)sender;
- (IBAction)setSerialPort:(id)sender;
- (void)driveNotification:(NSNotification *)note;
- (IBAction)goCoCo:(id)sender;

- (void)viewWireBugWindow:(id)sender;
- (void)viewPrinterWindow:(id)sender;

@end
