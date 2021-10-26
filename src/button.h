// https://arduinogetstarted.com/tutorials/arduino-button-debounce
#pragma once

class EventHandler;

class Button {
public:
  explicit Button(int iPinNum);
  
  virtual void Setup(EventHandler* pHandler = nullptr);
  virtual void Loop();

  bool IsDown();

private:
  EventHandler* pEventHandler;
  const int iPinNum;
  
  int iStateCurrent;
  int iStateSteady;
  int iStateFlicker;
  unsigned long uStateChangeTimeMS; // Time at which the state changed
};
