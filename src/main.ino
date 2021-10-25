#include "sdcard.h"


SDCard sdCard;

// The setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  // Setup our components
  sdCard.Setup();
}

// the loop function runs over and over again forever
void loop() {
  sdCard.Loop();
}
