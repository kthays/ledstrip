#include "components.h"
#include "pins.h"

Components::Components()
: buttonSettings(PIN_BUTTON_SETTINGS)
{

}

void Components::Setup(EventHandler* pEventHandler)
{
    sdCard.Setup(pEventHandler);
    buttonSettings.Setup(pEventHandler);
}

void Components::Loop()
{
    buttonSettings.Loop();
    sdCard.Loop();
}
