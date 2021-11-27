// https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-photoresistor-46c5eb

#pragma once
#include <Arduino.h>

class LightSensor {
public:
  LightSensor();
  void Setup();
  void Loop();
  
  // Calibration defines the day-night threshold value
  void SetCalibration(int iThreshold);
  int GetCalibration() const;

  // Returns the current light sensor reading
  int GetValue() const;

private:
  int iValue;
  int iThreshold;
  bool bIsDay; // Is the current value definitely above the threshold?
};
