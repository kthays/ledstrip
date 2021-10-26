// Components - a module containing all hardware components for the project

#pragma once
#include "sdcard.h"

class EventHandler;

struct Components {
    // Calls 'Setup(pEventHandler)' on all member components
    void Setup(EventHandler* pEventHandler);

    // Calls 'Loop()' on all member components
    void Loop();


    SDCard sdCard; // Pins 8, 10, 11, 12, 13
};
