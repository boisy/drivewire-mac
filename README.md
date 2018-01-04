# DriveWire
This is the official DriveWire server for macOS.

### DriveWire Specification: https://sourceforge.net/p/drivewireserver/wiki/DriveWire_Specification/


## AppleScript Support
You can use AppleScript to communicate with DriveWire server for macOS using the Script Editor application on the Mac. Below are several "recipes" that you can use. Note that they all talk to the "first document" but you can also reference a document by name if you have more than one opened.


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
        eject drive 3
    end tell
end tell
```

### Insert virtual disk "mydisk.dsk" into drive 0:
```AppleScript
tell application "DriveWire"
    tell server of first document
        insert image POSIX path of ("/Users/boisy/mydisk.dsk") into drive 0
    end tell
end tell
```
Note that the *insert* command will first eject any virtual disk from the drive before inserting the new one.

### Create a new document, set the machine type to CoCo 2, and insert a few disk images:
```AppleScript
tell application "DriveWire"
    set newDocument to make new document
    tell server of newDocument
        set machine to coco2
        insert image POSIX path of ("/Users/boisy/nitros9.dsk") into drive 0
        insert image POSIX path of ("/Users/boisy/utilities.dsk") into drive 1
    end tell
end tell
```


