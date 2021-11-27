// This module represents all of the high-level state data of the project

#pragma once
#include "patterns.h"

struct Data {
    static Data& GetInstance();

    void Loop(); // Calls Loop() for all data

    bool bIsStripOn; // TODO: we might end up replacing this with a member variable in the LED strip class

    bool bIsDay;
    CyclicPatternList patternList;
    int iDimmerPercent; // 0 = off, 100 = full brightness

private:
    Data();
};
