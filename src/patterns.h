
#define PATTERN_STR_LEN 16  // 8.3 files

// ** Pattern - Metadata for a pattern, includes the file path on the SD card to the pattern data, and how fast it should go
class Pattern {
public:
    Pattern(const char* szcFilePath, int iTimePerRowMS);

    const char* GetFilePath() const;
    int GetTimePerRowMS() const;

private:
    friend class CyclicPatternList; // Give the list container access to the pNext var
    Pattern* pNext;

    char szcFilePath[PATTERN_STR_LEN];
    int iTimePerRowMS;
};

// ** CyclicPatternList - A linked list of Pattern objects that loops back around to the first element after the last element
class CyclicPatternList {
public:
    CyclicPatternList();
    ~CyclicPatternList();

    // Takes ownership of the given pattern and appends it to the end of the list
    void AddPattern(Pattern* pPattern);

    const Pattern* GetCurrentPattern() const;
    void Advance(); // Advance the current pattern to the next in the list

    // Destroys all patterns contained in the list, resets current pattern to nullptr
    void Clear();

private:
    Pattern* pFirst;
    Pattern* pLast;
    Pattern* pCurrent;
};
