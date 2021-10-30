#include "dimmer.h"
#include "eventhandler.h"
#include "pins.h"

// Dimmer value has to change this much in order to trigger an event
#define DIMMER_EVENT_DELTA 2

Dimmer::Dimmer()
: iLastEventValue(0)
{
    
}

void Dimmer::Setup()
{

}

void Dimmer::Loop()
{
  const int iCurValue = GetReading();

  // See if the average value changed
  if (abs(iCurValue - iLastEventValue) > DIMMER_EVENT_DELTA) {
     EventHandler::GetInstance().EvDimmer(iCurValue);
    iLastEventValue = iCurValue;
  }
}


int Dimmer::GetReading()
{
    return map(analogRead(PIN_DIMMER), 0, 1023, 0, 100);
}
