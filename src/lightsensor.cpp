#include "lightsensor.h"
#include "eventhandler.h"
#include "pins.h"

// The day->night event won't trigger unless 
// the value has gone at least this far past the threshold value
#define LIGHTSENSOR_THRESHOLD_BUFFER  10

LightSensor::LightSensor()
: iValue(0)
, iThreshold(0)
, bIsDay(false)
{
  
}

void LightSensor::Setup()
{
  iValue = analogRead(PIN_LIGHTSENSOR);
  Calibrate();
}

void LightSensor::Loop()
{
  iValue = analogRead(PIN_LIGHTSENSOR);
  
  // Check for a Night -> Day event
  if ((!bIsDay) && (iValue > (iThreshold + LIGHTSENSOR_THRESHOLD_BUFFER))) {
      bIsDay = true;
      EventHandler::GetInstance().EvLightSensor(true);
  }
  
  // Check for a Day -> Night event
  else if (bIsDay && (iValue < (iThreshold - LIGHTSENSOR_THRESHOLD_BUFFER))) {
    bIsDay = false;
    EventHandler::GetInstance().EvLightSensor(false);
  }
}

void LightSensor::Calibrate()
{
  iThreshold = analogRead(PIN_LIGHTSENSOR);
  Serial.print("Light Calibration: ");
  Serial.println(iThreshold);
}