// The EventHandler module coordinates events from different modules
// and performs all of the high-level logic for the project

#pragma once
#include "components.h"
#include "data.h"

class EventHandler {
public:
    EventHandler(Components& components, Data& data);

    // Component level events
    void EvSDCardIn();

    // Logic events
    // ...

private:
    Components& components;
    Data& data;
};
