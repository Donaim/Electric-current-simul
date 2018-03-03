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

struct AtomRecConstructor : public AtomConstructor {
    virtual Atom * construct(const AtomBase& base, const NCreatorParams& p) const override;
};