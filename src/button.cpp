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
, iLightCurrent(0)
, iLightStart(0)
, iLightEnd(0)
, uEaseTimeStart(0)
{

}

void ButtonLED::Setup()
{
  Button::Setup();
  pinMode(PIN_BUTTON_POWER_5V, OUTPUT);
}

// Ease between start and end, t between 0 and 1
int EaseFunction(float t, int iStart, int iEnd) {
  t = constrain(t, 0.0, 1.0);
  t = t < 0.5 ? 8 * t * t * t * t : 1 - pow(-2 * t + 2, 4) / 2; // https://easings.net/#easeInOutQuart
  return (iStart * (1.0f - t)) + (iEnd * t);
}

void ButtonLED::Loop()
{
  Button::Loop();

  // Check if we should ease the LED brightness value
  if (iLightCurrent != iLightEnd) {
    float t = float(millis() - uEaseTimeStart) / float(BUTTON_LIGHT_EASE_TIME_MS);
    SetBrightness(EaseFunction(t, iLightStart, iLightEnd));
  }
}

void ButtonLED::SetBrightness(int iPercent)
{
  iLightCurrent = constrain(iPercent, 0, 100);
  
  // Max output for analogWrite is 255
  analogWrite(PIN_BUTTON_POWER_5V, map(iLightCurrent, 0, 100, 0, 255));
}

void ButtonLED::LightEase(bool bEaseOn)
{
  uEaseTimeStart = millis();
  iLightStart = bEaseOn ? BUTTON_LIGHT_MIN : BUTTON_LIGHT_MAX;
  iLightEnd = bEaseOn ? BUTTON_LIGHT_MAX : BUTTON_LIGHT_MIN;

  // Loop will take care of the rest
}
