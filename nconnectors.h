#pragma once

#include "network.h"

#define MAX_CONNECTION_DIST 1.0f

class Connector {
public:
    virtual void connect (const Network& net) const = 0;
};
