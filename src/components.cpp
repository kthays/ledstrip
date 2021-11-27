#include "components.h"
#include "data.h"
#include "pins.h"

Components& Components::GetInstance()
{
    static Components instance;
    return instance;
}

Components::Components()
: buttonSettings(PIN_BUTTON_SETTINGS)
, buttonPower(PIN_BUTTON_POWER_NO)
{

}

void Components::Setup()
{
    dimmer.Setup();
    lightSensor.Setup();
    sdCard.Setup();
    buttonSettings.Setup();
    buttonPower.Setup();

    const Data& data = Data::GetInstance();
    lightSensor.SetCalibration(data.storage.iLightSensorCalibration);
}

void Components::Loop()
{
    buttonSettings.Loop();
    buttonPower.Loop();
    dimmer.Loop();
    lightSensor.Loop();
    sdCard.Loop();
}
