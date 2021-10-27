#pragma once
#include <Arduino.h>

#define PATTERN_FILE_STR_LEN    16          // 8.3 files
#define PATTERN_ROW_DATA_BYTES  (120 * 3)     // 120 pixels per row * 3 bytes per pixel (RGB)


// ** Pattern - Metadata for a pattern, includes the file path on the SD card to the pattern data, and how fast it should go
class Pattern {
public:
    Pattern(const char* szcFilePath,  unsigned long uFileSizeBytes, int iTimePerRowMS);

    const char* GetFilePath() const;
    
    int GetCurrentRow() const;
    int GetTimePerRowMS() const;

    uint8_t* GetRowData();
    int GetRowDataSizeBytes() const;


    void PrintPatternData(int iPixelsToDisplay) const; // Print the first n values of the data array
    void PrintPixelData(int iPixelNumber) const; // 0 prints the first 3 bytes, 1 prints the next 3 bytes, etc.


private:
    friend class CyclicPatternList; // Give the list container access to the pNext var
    Pattern* pNext;

    static uint8_t arRowData[PATTERN_ROW_DATA_BYTES];
    int iRowCount;  // Determined by file size
    int iCurRow;
    int iTimePerRowMS;

    char szcFilePath[PATTERN_FILE_STR_LEN];
};


// ** CyclicPatternList - A linked list of Pattern objects that loops back around to the first element after the last element
class CyclicPatternList {
public:
    CyclicPatternList();
    ~CyclicPatternList();

    // Takes ownership of the given pattern and appends it to the end of the list
    void AddPattern(Pattern* pPattern);

    Pattern* GetCurrentPattern();
    void Advance(); // Advance the current pattern to the next in the list

    // Destroys all patterns contained in the list, resets current pattern to nullptr
    void Clear();

    // For debugging only - display the contents of the list
    void Print();


private:
    Pattern* pFirst;
    Pattern* pLast;
    Pattern* pCurrent;
};
