#include "patterns.h"
#include "string.h"

#include <Arduino.h> // Only needed for Serial.Print

// ** Pattern
uint8_t Pattern::arRowData[PATTERN_ROW_DATA_BYTES] = {0};

Pattern::Pattern(const char* _szcFilePath, unsigned long uFileSizeBytes, int _iTimePerRowMS)
: pNext(nullptr)
, iRowCount(uFileSizeBytes / PATTERN_ROW_DATA_BYTES)
, iCurRow(0)
, iTimePerRowMS(_iTimePerRowMS)
{
    strlcpy(szcFilePath, _szcFilePath, PATTERN_FILE_STR_LEN);
}

const char* Pattern::GetFilePath() const
{
    return szcFilePath;
}

int Pattern::GetCurrentRow() const
{
    return iCurRow;
}

int Pattern::GetTimePerRowMS() const
{
    return iTimePerRowMS;
}

uint8_t* Pattern::GetRowData()
{
    return arRowData;
}

int Pattern::GetRowDataSizeBytes() const
{
    return PATTERN_ROW_DATA_BYTES;
}


void Pattern::PrintPatternData(int iPixelsToDisplay) const
{
    for (int i = 0; i < iPixelsToDisplay; i++) PrintPixelData(i);
}


void Pattern::PrintPixelData(int iPixelNumber) const
{
    const int iCurIndex = iPixelNumber * 3;
    Serial.print("[");
    Serial.print(arRowData[iCurIndex + 0]); Serial.print(", ");
    Serial.print(arRowData[iCurIndex + 1]); Serial.print(", ");
    Serial.print(arRowData[iCurIndex + 2]); 
    Serial.println("]");
}


// ** CyclicPatternList
CyclicPatternList::CyclicPatternList()
: pFirst(nullptr)
, pLast(nullptr)
, pCurrent(nullptr)
{

}

CyclicPatternList::~CyclicPatternList()
{
    // Destroy the list contents
    Clear();
}

// Takes ownership of the given pattern and appends it to the end of the list
void CyclicPatternList::AddPattern(Pattern* pPattern)
{
    // Special case where the list is empty0
    if (pFirst == nullptr) {
        pFirst = pPattern;
        pCurrent = pPattern;
        pLast = pPattern;
        return;
    }

    // Append the new pattern to the end of the list
    if (pLast != nullptr) pLast->pNext = pPattern;
    pLast = pPattern;
}

Pattern* CyclicPatternList::GetCurrentPattern()
{
    return pCurrent;
}

void CyclicPatternList::Advance()
{
    if (pCurrent != nullptr) pCurrent = pCurrent->pNext;
    if (pCurrent == nullptr) pCurrent = pFirst; // Loop back around
}

void CyclicPatternList::Clear()
{
    // Delete all patterns in the list
    while (pFirst != nullptr) {
        pCurrent = pFirst->pNext;
        delete pFirst;
        pFirst = pCurrent;
    }

    // Reset state
    pFirst = nullptr;
    pCurrent = nullptr;
    pLast = nullptr;
}

void CyclicPatternList::Print()
{
    Serial.println("Pattern List:");

    const Pattern* pCur = pFirst;
    while (pCur != nullptr) {
        Serial.print(pCur->GetFilePath());
        Serial.print(": ");
        Serial.print(pCur->GetTimePerRowMS());
        Serial.println(" ms");
        pCur = pCur->pNext;
    }
}
