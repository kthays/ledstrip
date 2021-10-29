// This module represents all of the high-level state data of the project

#pragma once
#include "patterns.h"

struct Data {
    void Loop(); // Calls Loop() for all data

    CyclicPatternList patternList;
};
