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

        Serial.print("Current pattern is: ");
        if (data.GetCurrentPattern() != nullptr) Serial.println(data.GetCurrentPattern()->GetFilePath());
        else Serial.println("Nullptr!");
    }
    
}

void EventHandler::EvSDCardIn()
{
    Serial.println("Reloading pattern list");
    components.sdCard.LoadPatternsFromFile(data.patternList);
    data.patternList.Print();
}
