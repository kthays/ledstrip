// The EventHandler module coordinates events from different modules
// and performs all of the high-level logic for the project

#pragma once
#include "components.h"
#include "data.h"

class Button;
class EventHandler {
public:
    EventHandler(Components& components, Data& data);

    // Component level events
    void EvButton(Button* pButton);
    void EvButtonSettings(bool bButtonDown);

    
    void EvSDCardIn();


    // Logic events
    // ...

private:
    Components& components;
    Data& data;
};
