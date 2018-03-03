#pragma once

#include "network.cpp"
#include "atom_rec.h"
#include "helpers.cpp"
#include "network_creator_params.cpp"

class NetworkRec : public ConnectedNetwork {
    friend class AtomRec;
protected:
    SList<Atom*> aquenue{1000};
    AtomRec ** atomsrec;
public:
    NetworkRec(AtomCollection& net, const NCreatorParams& p);
    
    virtual void lap() override ;
};


struct RecConstructor : NetworkConstructor {
    virtual ConnectedNetwork& construct(AtomCollection& base, const NCreatorParams& p) const override {
        return *new NetworkRec(base, p);
    }
};
