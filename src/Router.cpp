#include "Router.h"

long long Router::nextRouterID = 1;

Router::Router() : Node("Router"+nextRouterID++) { // default is 4 ports
    for (int i = 1; i <= 4; i++) {
        addInterface();
    }
}

Router::Router(int portsNumber) : Node("Router"+nextRouterID++) {
    for (int i = 1; i <= portsNumber; i++) {
        addInterface();
    }
}