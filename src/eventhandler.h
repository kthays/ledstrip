// The EventHandler module coordinates events from different modules
// and performs all of the high-level logic for the project

#pragma once
#include "components.h"
#include "data.h"

class Button;
class EventHandler {
public:
    static EventHandler& GetInstance();

    // Component level events
    void EvButton(Button* pButton);
    void EvButtonSettings(bool bButtonDown);
    void EvDimmer(int iValue);
    void EvLightSensor(bool bIsDay);
    void EvSDCardIn();

    // Logic events
    void EvPatternChanged();
    void EvPatternRowChanged();

private:
    EventHandler();
    Components& components;
    Data& data;
};
