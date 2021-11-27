#include "data.h"
#include <EEPROM.h>

#define EEPROM_ADDR 0

Data::Data() 
: iDimmerPercent(0)
, bIsDay(false)
, bIsStripOn(false)
{
    
}

Data& Data::GetInstance()
{
    static Data instance;
    return instance;
}

void Data::Loop()
{
    // Update the current pattern row, based on time passed
    patternList.Loop();

}

void Data::Setup()
{
    storage.Read();
}


DataEEPROM::DataEEPROM()
: iLightSensorCalibration(0)
{

}

void DataEEPROM::Read()
{
    Serial.println("Reading data");
    Print();
    EEPROM.get(EEPROM_ADDR, *this);
}

void DataEEPROM::Write() const
{
    Serial.println("Writing data");
    EEPROM.put(EEPROM_ADDR, *this);
    Print();
}

void DataEEPROM::Print() const
{
    Serial.print(iLightSensorCalibration);
    Serial.println();
}