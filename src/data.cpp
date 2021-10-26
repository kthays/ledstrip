#include "data.h"

Data::Data()
{

}

const Pattern* Data::GetCurrentPattern() const
{
    return patternList.GetCurrentPattern();
}
