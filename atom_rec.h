#pragma once

#include "atom.cpp"
#include "network_rec.h"

class NetworkRec;

class AtomRec : public Atom {
public:
    NetworkRec * net;
    AtomRec(AtomBase b) : Atom(b) {}
    virtual void turn() override;
};