#pragma once

#include "network.cpp"
#include "atom_rec.h"
#include "helpers.cpp"

class NetworkRec : ConnectedNetwork {
    friend class AtomRec;
protected:
    SList<Atom*> aquenue{1000};
    AtomRec ** atomsrec;
public:
    NetworkRec(AtomCollection& net, const NCreatorParams& p);
    
    virtual void lap() override ;
};