#include "data.h"

Data::Data() 
: iDimmerPercent(0)
, bIsDay(false)
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
