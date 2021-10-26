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
    if (bButtonDown) Serial.println("Button Down");
    else Serial.println("Button Up");
}

void EventHandler::EvSDCardIn()
{
    Serial.println("Reloading pattern list");
    components.sdCard.LoadPatternsFromFile(data.patternList);

    data.patternList.Print();
}
