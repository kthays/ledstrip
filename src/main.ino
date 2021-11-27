#include "components.h"
#include "eventhandler.h"
#include "data.h"

Components& components = Components::GetInstance();
Data& data = Data::GetInstance();

// The setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  // Setup our components
  data.Setup();
  components.Setup();
}

// The loop function runs over and over again forever
void loop() {
  data.Loop();
  components.Loop();
}
