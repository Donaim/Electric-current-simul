#pragma once

#include "atom_collection.h"

#define MAX_CONNECTION_DIST 1.0f

class Connector {
public:
    virtual void connect (const AtomCollection& net) const = 0;
};
