// https://www.arduino.cc/en/reference/SD
// https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390
// https://arduinojson.org/v6/example/config/
//
// Pinout as specified by https://store-usa.arduino.cc/products/arduino-nano?selectedStore=us
//  10: CS
//  11: MOSI
//  12: MISO
//  13: SCK
//
//  Note: Files must be in 8.3 format
#pragma once
#include <SD.h>
#include "patterns.h"

// Note: using .js instead of .json since the sd module can only handle 8.3 filenames
#define SDCARD_FILE_PATTERNS  "patterns.js"

class SDCard {
public:
    SDCard();

    void Setup();
    void Loop();

    // Populates |list| with the patterns described in |SDCARD_FILE_PATTERNS|
    //  Note: Clears the list before re-populating it
    void LoadPatternsFromFile(CyclicPatternList& list);

private:
    void PrintDirectoryRoot();
    void PrintDirectory(File dir, int numTabs);

    bool LoadPatternConfig(const char* szcFileName);

};
