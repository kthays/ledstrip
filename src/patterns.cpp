#include "patterns.h"
#include "string.h"

#include <Arduino.h> // Only needed for Serial.Print

// ** Pattern
Pattern::Pattern(const char* _szcFilePath, int _iTimePerRowMS)
: pNext(nullptr)
, iTimePerRowMS(_iTimePerRowMS)
{
    strlcpy(szcFilePath, _szcFilePath, PATTERN_STR_LEN);
}

const char* Pattern::GetFilePath() const
{
    return szcFilePath;
}

int Pattern::GetTimePerRowMS() const
{
    return iTimePerRowMS;
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

const Pattern* CyclicPatternList::GetCurrentPattern() const
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
