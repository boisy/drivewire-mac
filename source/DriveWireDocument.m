//
//  DriveWireDocument.m
//  DriveWire
//
//  Created by Boisy Pitre on 12/23/04.
//  Copyright __MyCompanyName__ 2004 . All rights reserved.
//

#import "DriveWireDocument.h"
#import "VirtualScreenWindowController.h"

#define MODULE_HASHTAG "DriveWireDocument"

@implementation DriveWireDocument


+ (void)initializeDefaults;
{
    NSDictionary *initialValues = [NSDictionary dictionaryWithObjectsAndKeys:
                                   [NSNumber numberWithBool:TRUE], @"ApplePersistenceIgnoreState",
                                   nil];
    
    [[NSUserDefaults standardUserDefaults] registerDefaults:initialValues];
}

+ (void)initialize;
{
    if ([[self className] isEqualToString:[DriveWireDocument className]])
    {
        // Initialize our defaults right away
        [DriveWireDocument initializeDefaults];
    }
}

#pragma mark -
#pragma mark Init/Dealloc

- (id)init;
{
    if (self = [super init])
	{
		// All of our initialization is done in windowControllerDidLoadNib
        self.log = [TBLog sharedLog];
	}

    return self;
}

- (void)dealloc;
{
	NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
	NSMutableArray *driveArray = [self.dwModel driveArray];
	
	// Remove observer of printer messages
    [nc removeObserver:self.printerWindowController name:@"DWPrint" object:self.dwModel];
    [nc removeObserver:self name:kVirtualScreenOpenedNotification object:self.dwModel];
    [nc removeObserver:self name:kVirtualScreenClosedNotification object:self.dwModel];

	for (int i = 0; i < [driveArray count]; i++)
	{
		// Remove ourself as an observer of cartridge insert/eject messages for each drive
		[nc removeObserver:self name:@"cartridgeWasInserted" object:[driveArray objectAtIndex:i]];
		[nc removeObserver:self name:@"cartridgeWasEjected" object:[driveArray objectAtIndex:i]];
	}
    
    [self removeWindowController:self.printerWindowController];
    [self removeWindowController:self.debuggerWindowController];
}

- (NSString *)windowNibName;
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"DriveWireDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *)aController;
{
    int i;
    NSString *currentPort, *portTitle = nil;
	
    [aController setShouldCloseDocument:YES];
    
    myWindowController = aController;

    if (self.dwModel == nil)
    {
        self.dwModel = [[DriveWireServerModel alloc] initWithDocument:self version:DW_DEFAULT_VERSION];
    }
    
    [self.dwModel setDelegate:self];
    
    // add our window controllers
    [self addWindowController:self.printerWindowController];
    [self addWindowController:self.debuggerWindowController];
    
    // Call super class
    [super windowControllerDidLoadNib:aController];
	
    // Request the array of ports from the Document Model	
	NSMutableDictionary *portNames = [[TBSerialManager defaultManager] availablePorts] ;

	// Remove all items from the port button
	[serialPortButton removeAllItems];
	
	// Get the selected serial port, if any
	currentPort = [self.dwModel serialPort];
   
	// Iterate through the list of names and add each to the list
	{
		NSEnumerator *e = [portNames keyEnumerator];
		NSString *n;
		
		[serialPortButton addItemWithTitle:@"No Device"];

		while ((n = [e nextObject]))
		{
			TBDebug(@"%@ is available\n", n);
			[serialPortButton addItemWithTitle:n];
			if (currentPort != nil && [currentPort compare:n] == NSOrderedSame)
			{
				portTitle = n;
			}
		}
	}

	// Select the model's port, if not nil, else select the 0th indexed item ("No Device")
	if (portTitle == nil)
	{
		[serialPortButton selectItemAtIndex:0];
		lastPortSelected = 0;
	}
	else
	{
		[serialPortButton selectItemWithTitle:portTitle];
		lastPortSelected = [serialPortButton indexOfSelectedItem];
	}

	// Get the array of drives from the Document Model
	NSMutableArray *driveArray = [self.dwModel driveArray];
	
	NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
	
	for (i = 0; i < [driveArray count]; i++)
	{
		[driveView addSubview:[[driveArray objectAtIndex:i] view]];

		// Add ourself as an observer of cartridge insert/eject messages for each drive
		[nc addObserver:self selector:@selector(driveNotification:) name:@"cartridgeWasInserted" object:[driveArray objectAtIndex:i]];
		[nc addObserver:self selector:@selector(driveNotification:) name:@"cartridgeWasEjected" object:[driveArray objectAtIndex:i]];
		TBDebug(@"Observing for object: 0x%@", [driveArray objectAtIndex:i]);
	}
    
    [nc addObserver:self
           selector:@selector(screenOpened:)
               name:kVirtualScreenOpenedNotification
             object:self.dwModel];
    
    [nc addObserver:self
           selector:@selector(screenClosed:)
               name:kVirtualScreenClosedNotification
             object:self.dwModel];
    
    // Add the printerWindowController as an observer of print messages
    [nc addObserver:self.printerWindowController selector:@selector(updatePrintBuffer:) name:@"DWPrint" object:self.dwModel];
    
    [machineTypePopupButton selectItemWithTag:self.dwModel.machineType];
    [self updateUIComponents];
}


#pragma mark DriveWire Protocol Delegate Methods

- (void)updateMemoryView:(NSDictionary *)info;
{
    [self.debuggerWindowController updateMemory:info];
}

- (void)updateRegisterView:(NSDictionary *)info;
{
    [self.debuggerWindowController updateRegisters:info];
}

- (void)updatePrinterView:(NSDictionary *)info;
{
    [self.printerWindowController updatePrintBuffer:[info objectForKey:@"PrintData"]];
}

- (void)updateUIComponents;
{
    switch ([self.dwModel machineType])
    {
        case MachineTypeCoCo1_38_4:
        case MachineTypeCoCo1_57_6:
            [machineImageView setImage:[NSImage imageNamed:@"CoCo1"]];
            break;

        case MachineTypeCoCo2_57_6:
            [machineImageView setImage:[NSImage imageNamed:@"CoCo2"]];
            break;
           
        case MachineTypeCoCo3_115_2:
        default:
            [machineImageView setImage:[NSImage imageNamed:@"CoCo3"]];
            break;

        case MachineTypeAtariLiber809_57_6:
            [machineImageView setImage:[NSImage imageNamed:@"Atari"]];
            break;
    }
}

- (NSData *)dataRepresentationOfType:(NSString *)aType;
{
    return [NSKeyedArchiver archivedDataWithRootObject:self.dwModel];
}

- (BOOL)loadDataRepresentation:(NSData *)data ofType:(NSString *)aType;
{
	self.dwModel = [NSKeyedUnarchiver unarchiveObjectWithData:data];
	
	return YES;
}

- (IBAction)setSerialPort:(id)sender;
{
	NSString *thePort = [serialPortButton titleOfSelectedItem];
	
	// Ask the Document Model to open thePort
	if ([self.dwModel setCommPort:thePort] == NO)
	{
		NSAlert *errorAlert = [NSAlert alertWithMessageText:@"Communications Error"
											   defaultButton:@"OK"
											alternateButton:nil
												otherButton:nil
								  informativeTextWithFormat:@"The port \"%@\" failed to open.", thePort];
		
		[errorAlert runModal];
		
		[serialPortButton selectItemAtIndex:lastPortSelected];
		
		return;
	}
	
	lastPortSelected = [sender indexOfSelectedItem];

	[self updateChangeCount:NSChangeDone];
}

- (void)driveNotification:(NSNotification *)note;
{
	[self updateChangeCount:NSChangeDone];
}

- (IBAction)setCoCoType:(NSPopUpButton *)sender;
{
    MachineType machineType = [sender selectedTag];
    [self.dwModel setMachineType:machineType];
   
    [self updateUIComponents];
}

- (IBAction)goCoCo:(id)sender;
{
   [self.dwModel goCoCo];
}

- (void)viewWireBugWindow:(id)sender;
{
    [self.debuggerWindowController showWindow:self];
}

- (void)viewPrinterWindow:(id)sender;
{
    [self.printerWindowController showWindow:self];
}

- (void)screenOpened:(NSNotification *)note;
{
    VirtualScreenWindowController *screen = [note.userInfo objectForKey:@"screen"];
    [self addWindowController:screen];
    [screen showWindow:self];
}

- (void)screenClosed:(NSNotification *)note;
{
    VirtualScreenWindowController *screen = [note.userInfo objectForKey:@"screen"];
    [screen close];
    [self removeWindowController:screen];
}

@end
