#include "button.h"
#include "eventhandler.h"

#define BUTTON_DEBOUNCE_DELAY_MS    50


Button::Button(int _iPinNum)
: pEventHandler(nullptr)
, iPinNum(_iPinNum)
, iStateCurrent(LOW)
, iStateSteady(LOW)
, iStateFlicker(LOW)
, uStateChangeTimeMS(0)
{
 
}

void Button::Setup(EventHandler* _pEventHandler) 
{
  pinMode(iPinNum, INPUT_PULLUP);
  pEventHandler = _pEventHandler;
}

void Button::Loop() 
{
  // Read the current button state
  iStateCurrent = digitalRead(iPinNum);
  
  // Reset the debounce timer on state change
  if (iStateCurrent != iStateFlicker) {
    uStateChangeTimeMS = millis();
    iStateFlicker = iStateCurrent;
  }
  
  // If we haven't seen flickering in the last 50 ms, check if the state changed
  if ((millis() - uStateChangeTimeMS) > BUTTON_DEBOUNCE_DELAY_MS) {
    
    // Did the state actually change?
    if (iStateSteady != iStateCurrent) {
      iStateSteady = iStateCurrent; // Set the steady state now, so the event handler can call IsDown
      if (pEventHandler != nullptr) pEventHandler->EvButton(this);
    }
    
    iStateSteady = iStateCurrent;
  }
}

bool Button::IsDown()
{
  return (iStateSteady == LOW);
}
