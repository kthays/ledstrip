#include "sdcard.h"
#include <SPI.h>
#include <ArduinoJson.h>

#define SDCARD_PIN_CS 10

SDCard::SDCard()
{
    
}

void SDCard::Setup()
{
  // Wait for serial port to connect. Needed for native USB port only
  while (!Serial) { ; }

  // Start the SD card reader
  if (!SD.begin(SDCARD_PIN_CS)) {
    Serial.println("Setup failed!");
    while (1);
  }

  Serial.println("Setup success!");

  // See if we can parse the file contents
  PrintDirectoryRoot();
}

void SDCard::Loop()
{

}

void SDCard::PrintDirectoryRoot()
{
  File root = SD.open("/");
  PrintDirectory(root, 0);
}

void SDCard::PrintDirectory(File dir, int numTabs) 
{
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) break;

    // Print the tabs
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }

    // Print the current entry
    Serial.print(entry.name());

    // Recursively print subdirectory
    if (entry.isDirectory()) {
      Serial.println("/");
      PrintDirectory(entry, numTabs + 1);
    } else {
      // Print the file size
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }

    // Cleanup
    entry.close();
  }
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
