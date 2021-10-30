#include "components.h"
#include "pins.h"

Components& Components::GetInstance()
{
    static Components instance;
    return instance;
}

Components::Components()
: buttonSettings(PIN_BUTTON_SETTINGS)
{

}

void Components::Setup()
{
    sdCard.Setup();
    buttonSettings.Setup();
}

void Components::Loop()
{
    buttonSettings.Loop();
    dimmer.Loop();
    sdCard.Loop();
}
