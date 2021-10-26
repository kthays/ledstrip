#include "components.h"
#include "eventhandler.h"
#include "data.h"

Components components;
Data data;
EventHandler eventHandler(components, data);

// The setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  // Setup our components
  components.Setup(&eventHandler);
}

// The loop function runs over and over again forever
void loop() {
  components.Loop();
}
