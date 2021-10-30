// Components - a module containing all hardware components for the project

#pragma once
#include "button.h"
#include "dimmer.h"
#include "sdcard.h"

struct Components {

    // Use a singleton pattern since we'll never need more than one instance of this
    static Components& GetInstance();

    // Calls 'Setup()' on all member components
    void Setup();

    // Calls 'Loop()' on all member components
    void Loop();

    Dimmer dimmer;  // Pin A0
    Button buttonSettings; // Pin 7
    SDCard sdCard; // Pins 8, 10, 11, 12, 13
    
private:
    Components();
};
