#include "eventhandler.h"

EventHandler::EventHandler(Components& _components, Data& _data)
: components(_components)
, data(_data)
{

}

// Component events
void EventHandler::EvSDCardIn()
{
    Serial.println("Reloading pattern list");
    components.sdCard.LoadPatternsFromFile(data.patternList);

    data.patternList.Print();
}
