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
 }

void EventHandler::EvButtonSettings(bool bButtonDown)
{
    // When the settings button is pressed, advance to the next pattern
    if (bButtonDown) {
        data.patternList.Advance();
        EvPatternChanged();
    }
    
}

void EventHandler::EvDimmer(int iValue)
{
    Serial.print("Dimmer: "); Serial.println(iValue);
    data.iDimmerPercent = iValue;
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
    //pCurPattern->PrintPatternData(5);
}

void EventHandler::EvPatternRowChanged()
{
    Pattern* pCurPattern = data.patternList.GetCurrentPattern();
    if (pCurPattern == nullptr) return;
    //Serial.print("Row "); Serial.println(pCurPattern->GetCurrentRow());
}
