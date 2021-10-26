#include "components.h"

void Components::Setup(EventHandler* pEventHandler)
{
    sdCard.Setup(pEventHandler);
}

void Components::Loop()
{
    sdCard.Loop();
}
