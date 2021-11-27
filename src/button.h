// https://arduinogetstarted.com/tutorials/arduino-button-debounce
#pragma once

class EventHandler;

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

  void SetBrightness(int iPercent);

private:
  
};