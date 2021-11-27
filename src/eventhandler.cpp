#include "eventhandler.h"

EventHandler& EventHandler::GetInstance()
{
    static EventHandler instance;
    return instance;
}

EventHandler::EventHandler()
: components(Components::GetInstance())
, data(Data::GetInstance())
{

}

// Component events

 void EventHandler::EvButton(Button* pButton)
 {
 
    if (pButton == &components.buttonSettings) EvButtonSettings(pButton->IsDown());
    if (pButton == &components.buttonPower) EvButtonPower(pButton->IsDown());

    // Calibrate when pressing both buttons
    if (components.buttonPower.IsDown() && components.buttonSettings.IsDown()) EvCalibrate();
 }

void EventHandler::EvButtonSettings(bool bButtonDown)
{
    // When the settings button is pressed, advance to the next pattern
    if (bButtonDown) {
        data.patternList.Advance();
        EvPatternChanged();
        Serial.println("Settings button");
    }
    
}

void EventHandler::EvButtonPower(bool bButtonDown)
{
    // When the power button is pressed, toggle the LED strip's "on" state,
    // and initiate the button light transition
    if (bButtonDown) {
        data.bIsStripOn = !data.bIsStripOn;
        if (data.bIsStripOn) Serial.println("Lights On");
        else Serial.println("Lights Off");
        components.buttonPower.LightEase(data.bIsStripOn);
    }
}

void EventHandler::EvDimmer(int iValue)
{
    Serial.print("Dimmer: "); Serial.println(iValue);
    data.iDimmerPercent = iValue;
}

void EventHandler::EvLightSensor(bool bIsDay)
{
    if (bIsDay) Serial.println("Day time");
    else Serial.println("Night time");

    data.bIsDay = bIsDay;
}

void EventHandler::EvSDCardIn()
{
    Serial.println("Reloading pattern list");
    components.sdCard.LoadPatternsFromFile(&data.patternList);
    data.patternList.Print();
}


// Logic events
void EventHandler::EvPatternChanged()
{
    // Get the current pattern
    Pattern* pCurPattern = data.patternList.GetCurrentPattern();
    if (pCurPattern == nullptr) return;

    // Load the pattern data from the SD card into our values array
    components.sdCard.ReadPatternData(pCurPattern);
}

void EventHandler::EvPatternRowChanged()
{
    Pattern* pCurPattern = data.patternList.GetCurrentPattern();
    if (pCurPattern == nullptr) return;
    components.sdCard.ReadPatternData(pCurPattern);
}

void EventHandler::EvCalibrate()
{
    components.lightSensor.Calibrate();
}
