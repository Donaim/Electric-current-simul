#pragma once

#include "atom_collection.h"

#define MAX_CONNECTION_DIST 1.0f

class Connector {
public:
    virtual void connect (AtomCollection& net) const = 0;
};
