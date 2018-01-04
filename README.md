# DriveWire Server for macOS
This is the official DriveWire server for macOS. Integrations are performed as commits are made, and Sparkle is used for in-app updating. You can download the [latest build here](http://downloads.tandycolorcomputer.com/DriveWire.zip).


## AppleScript Support
You can use AppleScript to communicate with DriveWire server for macOS using the Script Editor application on the Mac. This is convenient if you want to automate your disk image creation and test workflow. Below are several "recipes" that you can use. Note that each script accesses the "first document" but you can also reference a document by name if you have more than one opened.


### Set the machine type:
```AppleScript
tell application "DriveWire"
    tell server of first document
        -- valid choices are: coco1, coco2, coco3, atari
        set machine to coco2
    end tell
end tell
```

### Eject the virtual disk in drive 3:
```AppleScript
tell application "DriveWire"
    tell server of first document
        -- an error is returned if the drive number is illegal
        eject drive 3
    end tell
end tell
```

### Insert virtual disk "mydisk.dsk" into drive 0:
```AppleScript
tell application "DriveWire"
    tell server of first document
        -- the insert command ejects any virtual disk from the drive before inserting the new one
        insert image POSIX path of ("/Users/boisy/mydisk.dsk") into drive 0
    end tell
end tell
```

### Create a new document, set the machine type to CoCo 2, and insert a few disk images:
```AppleScript
tell application "DriveWire"
    set newDocument to make new document
    tell server of newDocument
        set machine to coco2
        -- an error is returned if the drive number is illegal or the path does not exist
        insert image POSIX path of ("/Users/boisy/nitros9.dsk") into drive 0
        insert image POSIX path of ("/Users/boisy/utilities.dsk") into drive 1
    end tell
end tell
```

## DriveWire Specification
This server follows the specifications [found here]( https://sourceforge.net/p/drivewireserver/wiki/DriveWire_Specification/).


