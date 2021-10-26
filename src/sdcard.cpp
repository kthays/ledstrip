#include "sdcard.h"
#include <SPI.h>
#include <ArduinoJson.h>
#include "pins.h"

SDCard::SDCard()
: bIsCardIn(false)
{
    
}

void SDCard::Setup()
{
  pinMode(PIN_SDCARD_CD, INPUT_PULLUP);

  // Wait for serial port to connect. Needed for native USB port only
  while (!Serial) { ; }
}

void SDCard::Loop()
{
  const bool bCardInNow = IsCardIn();
  if (bIsCardIn != bCardInNow) {
    bIsCardIn = bCardInNow;
    Serial.println(bIsCardIn ? "Card In" : "Card Out");
    if (bIsCardIn) EvCardIn();
  }
}

bool SDCard::IsCardIn()
{
  return digitalRead(PIN_SDCARD_CD) == LOW;
}

void SDCard::LoadPatternsFromFile(CyclicPatternList& list)
{
  list.Clear();

  // Open the patterns JSON file
  File file = SD.open(SDCARD_FILE_PATTERNS);
  DynamicJsonDocument doc(file.size());

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println("Failed to read file");
    file.close();
    return;
  }

  // Read the document as an array
  JsonArrayConst array = doc.as<JsonArrayConst>();
  for (JsonVariantConst v: array) {
    JsonObjectConst obj = v.as<JsonObjectConst>();
    list.AddPattern(new Pattern(obj["file"], obj["speed"]));
  }

  file.close();
}

void SDCard::EvCardIn()
{
  // Re-initialize 
  if (SD.begin(PIN_SDCARD_CS)) Serial.println("Card Ready");
  else Serial.println("Failed to initialize SD module!");
}
