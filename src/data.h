// This module represents all of the high-level state data of the project

#pragma once
#include "patterns.h"

struct Data {
    static Data& GetInstance();

    void Loop(); // Calls Loop() for all data

    CyclicPatternList patternList;

private:
    Data();
};
