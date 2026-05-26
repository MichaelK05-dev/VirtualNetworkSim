#include "Hub.h"
#include "NetworkInterface.h"
#include "GlobalTypes.h"
#include "EthernetBus.h"
Hub::Hub(std::string name, int ports) : Node{name}
{
    for (int i = 0; i < 4; ++i)
    {
        addInterface();
    }
}
// Just redirects the incoming signal to all connected interfaces and checks for collision
void Hub::onTick()
{
    int signalsReceived = 0;
    Signal currentSignal = Signal::IDLE;
    NetworkInterface *currentInterface = nullptr;

    for (NetworkInterface *interface : getInterfaces("connected"))
    {
        if (interface->getBus()->current_signal != Signal::IDLE)
        {
            signalsReceived++;
            currentSignal = interface->getBus()->current_signal;
            currentInterface = interface;
        }
    }
    for (NetworkInterface *interface : getInterfaces("connected"))
    {
        if (signalsReceived <= 1)
        {
            if (interface != currentInterface)
            {
                interface->getBus()->reportSignal(currentSignal);
            }
        }
        else
        { // if collision, currentInterface must not be skipped
            interface->getBus()->reportSignal(Signal::COLLISION);
        }
    }
}

void Hub::resolveTick()
{
}