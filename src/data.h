// This module represents all of the high-level state data of the project

#pragma once
#include "patterns.h"

// Special data that gets saved in long-term memory (stays around after restarting)
struct DataEEPROM {
    DataEEPROM();
    void Read();
    void Write() const;
    void Print() const; // Debugging only


    int iLightSensorCalibration;
};


struct Data {
    static Data& GetInstance();

    void Setup(); // Loads storage data
    void Loop(); // Calls Loop() for all data

    bool bIsStripOn; // TODO: we might end up replacing this with a member variable in the LED strip class

    bool bIsDay;
    CyclicPatternList patternList;
    int iDimmerPercent; // 0 = off, 100 = full brightness

    DataEEPROM storage;

private:
    Data();
};

