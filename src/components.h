// Components - a module containing all hardware components for the project

#pragma once
#include "button.h"
#include "sdcard.h"

class EventHandler;

struct Components {
    Components();

    // Calls 'Setup(pEventHandler)' on all member components
    void Setup(EventHandler* pEventHandler);

    // Calls 'Loop()' on all member components
    void Loop();


    SDCard sdCard; // Pins 8, 10, 11, 12, 13
    Button buttonSettings; // Pin 7
};
