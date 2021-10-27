#include "sdcard.h"
#include <SPI.h>
#include <ArduinoJson.h>
#include "eventhandler.h"
#include "patterns.h"
#include "pins.h"


SDCard::SDCard()
: pEventHandler(nullptr)
, bIsCardIn(false)
{
    
}

void SDCard::Setup(EventHandler* _pEventHandler)
{
  pEventHandler = _pEventHandler;

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

void SDCard::LoadPatternsFromFile(CyclicPatternList* pList)
{
  if (pList == nullptr) return;
  CyclicPatternList& list = *pList;
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

  // Close the file asap, so we can open other files to get their sizes
  file.close();

  // Read the document as an array
  JsonArrayConst array = doc.as<JsonArrayConst>();
  for (JsonVariantConst v: array) {
    JsonObjectConst obj = v.as<JsonObjectConst>();
    const char* szcFileName = obj["file"];

    // Open the file to get its size, then close
    file = SD.open(szcFileName);
    const unsigned long uFileSize = file ? file.size() : -1;
    file.close();

    // Create a new pattern and add it to the list
    list.AddPattern(new Pattern(szcFileName, uFileSize, obj["speed"]));
  }

  file.close();
}

void SDCard::ReadPatternData(Pattern* pPattern)
{
  if (pPattern == nullptr) return;

  // Find where in the file we should copy row data from
  const unsigned long uRowSizeBytes = pPattern->GetRowDataSizeBytes();
  const unsigned long uRowStartByte = (unsigned long)(pPattern->GetCurrentRow()) * uRowSizeBytes;

  // Extract the data into the pattern buffer
  File file = SD.open(pPattern->GetFilePath());
  file.seek(uRowStartByte);
  file.readBytes(pPattern->GetRowData(), uRowSizeBytes);
  file.close();
}

void SDCard::EvCardIn()
{
  // Re-initialize 
  if (SD.begin(PIN_SDCARD_CS)) Serial.println("Card Ready");
  else Serial.println("Failed to initialize SD module!");

  if (pEventHandler != nullptr) pEventHandler->EvSDCardIn();
}
