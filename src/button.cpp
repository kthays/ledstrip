#include "button.h"
#include "eventhandler.h"
#include "pins.h"

#define BUTTON_DEBOUNCE_DELAY_MS    50


Button::Button(int _iPinNum)
: iPinNum(_iPinNum)
, iStateCurrent(LOW)
, iStateSteady(LOW)
, iStateFlicker(LOW)
, uStateChangeTimeMS(0)
{
 
}

void Button::Setup() 
{
  pinMode(iPinNum, INPUT_PULLUP);
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
      EventHandler::GetInstance().EvButton(this);
    }
    
    iStateSteady = iStateCurrent;
  }
}

bool Button::IsDown()
{
  return (iStateSteady == LOW);
}



// ** ButtonLED **
ButtonLED::ButtonLED(int iPinNO)
: Button(iPinNO)
{

}

void ButtonLED::Setup()
{
  Button::Setup();
  pinMode(PIN_BUTTON_POWER_5V, OUTPUT);
}

void ButtonLED::Loop()
{
  Button::Loop();
}

void ButtonLED::SetBrightness(int iPercent)
{
  const int iLightCurrent = constrain(iPercent, 0, 100);
  
  // Max output for analogWrite is 255
  analogWrite(PIN_BUTTON_POWER_5V, map(iLightCurrent, 0, 100, 0, 255));
}

