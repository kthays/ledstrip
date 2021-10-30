#pragma once
#include <Arduino.h>

class Dimmer {
public:
    Dimmer();

    void Setup();
    void Loop();

private:
    int GetReading();

    int iLastEventValue;
};
