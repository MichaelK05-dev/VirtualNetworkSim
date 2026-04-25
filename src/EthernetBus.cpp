#include "EthernetBus.h"

void EthernetBus::broadcast(EthernetFrame f) {
    for (NetworkInterface* interface : connectedInterfaces) {
        interface->receive(f);
    }
}