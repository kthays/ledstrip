// This module represents all of the high-level state data of the project

#pragma once
#include "patterns.h"

struct Data {
    Data();
    CyclicPatternList patternList;
    const Pattern* GetCurrentPattern() const;
};
