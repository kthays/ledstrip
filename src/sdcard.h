// https://www.arduino.cc/en/reference/SD
// https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390
// https://arduinojson.org/v6/example/config/
//
// Pinout as specified by https://store-usa.arduino.cc/products/arduino-nano?selectedStore=us
//  8:  CD
//  10: CS
//  11: MOSI
//  12: MISO
//  13: SCK
//
//  Note: Files must be in 8.3 format
#pragma once
#include <SD.h>

// Note: using .js instead of .json since the sd module can only handle 8.3 filenames
#define SDCARD_FILE_PATTERNS  "patterns.js"

class CyclicPatternList;
class Pattern;

class SDCard {
public:
    SDCard();

    void Setup();
    void Loop();

    // Populates |list| with the patterns described in |SDCARD_FILE_PATTERNS|
    //  Note: Clears the list before re-populating it
    void LoadPatternsFromFile(CyclicPatternList* pList);

    // Loads the pattern's current row data from the file to the pattern row buffer
    void ReadPatternData(Pattern* pPattern);

    // Check if the SD card is plugged in
    bool IsCardIn();

private:
    void EvCardIn(); // Call this every time the SD card is plugged in
    bool bIsCardIn;
};
