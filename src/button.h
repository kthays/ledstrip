// https://arduinogetstarted.com/tutorials/arduino-button-debounce
#pragma once
#define BUTTON_LIGHT_EASE_TIME_MS   750
#define BUTTON_LIGHT_MIN            0
#define BUTTON_LIGHT_MAX            100

class Button {
public:
  explicit Button(int iPinNum);
  
  virtual void Setup();
  virtual void Loop();

  bool IsDown();

private:
  const int iPinNum;
  
  int iStateCurrent;
  int iStateSteady;
  int iStateFlicker;
  unsigned long uStateChangeTimeMS; // Time at which the state changed
};

class ButtonLED:public Button {
public:
  explicit ButtonLED(int iPinNO);

  virtual void Setup() override;
  virtual void Loop() override;

  void LightEase(bool bEaseOn); // Ease the light on or off
  void SetBrightness(int iPercent);

private:
  // Brightness values are on a 0-100 scale
  int iLightCurrent;
  int iLightStart;
  int iLightEnd;

  unsigned long uEaseTimeStart;

};