#pragma once

#include "atom.cpp"
#include "network_creator_params.cpp"
#include "nconnectors.h"
#include "atom_collection.h"
#include <iostream>
#include <functional>


class ConnectedNetwork {
protected:
    Atom ** const atoms;
    const int a_count;

    static Atom ** connect(AtomCollection& net, const Connector& conn) {
        conn.connect(net);
        return net.atoms();
    }
public:
    ConnectedNetwork(AtomCollection& net, const NCreatorParams& p) :  atoms(connect(net, p.connector)), a_count(net.list.size()) 
    { }
    virtual void lap() {
        for (int i = 0; i < a_count; i++ ) {
            atoms[i]->turn();
        }
    }
    int total_charge() const {
        int re = 0;
        for (int i = 0; i < a_count; i++ ) {
            re += atoms[i]->charge();
        }
        return re;
    }
    float avg_abscharge() const {
        int sum = 0;
        for (int i = 0; i < a_count; i++ ) {
            sum += std::abs(atoms[i]->charge());
        }
        return sum / (float)a_count;
    }

    friend std::ostream& operator << (std::ostream& os, const ConnectedNetwork& o);
    ~ConnectedNetwork();
};


ConnectedNetwork::~ConnectedNetwork() {
    // std::cout << "destructed " << a_count << " atoms" << std::endl;
    for (int i = 0; i < a_count; i++ ){
        delete atoms[i];
    }
    delete[] atoms;
}
ostream& operator << (ostream& os, const ConnectedNetwork& o){
    for (int i = 0; i < o.a_count; i++) {
        os << *o.atoms[i] << ' ';
    }
    return os;
}


struct SimpleConstructor : NetworkConstructor {
    virtual ConnectedNetwork * construct(AtomCollection& base, const NCreatorParams& p) const override {
        return new ConnectedNetwork(base, p);
    }
};
