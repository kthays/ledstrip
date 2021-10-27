#include "eventhandler.h"

EventHandler::EventHandler(Components& _components, Data& _data)
: components(_components)
, data(_data)
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
    pCurPattern->PrintPatternData(5);
}
