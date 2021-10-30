// https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-photoresistor-46c5eb

#pragma once
#include <Arduino.h>

class LightSensor {
public:
  LightSensor();
  void Setup();
  void Loop();
  
  // Uses the current sensor reading as the day-night threshold value
  void Calibrate();

private:
  int iValue;
  int iThreshold;
  bool bIsDay; // Is the current value definitely above the threshold?
};
