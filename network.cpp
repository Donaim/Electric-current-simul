#pragma once

#include "atom.cpp"
#include <iostream>
#include <functional>

#define MAX_CONNECTION_DIST 1.0f

struct Network {
    AtomBase ** atoms;
    int a_count;
    ~Network() {
        // std::cout << "Network destructed" << std::endl;
        for (int i = 0; i < a_count; i++) {
            delete atoms[i];
        }
        delete[] atoms;
    }
};

class Connector {
public:
    virtual Atom ** connect (const Network& net) const = 0;
};


class ConnectedNetwork {
    Atom ** const atoms;
    const int a_count;
public:
    ConnectedNetwork(const Network& net, const Connector& conn) :  atoms(conn.connect(net)), a_count(net.a_count) 
    { }
    void lap() const {
        for (int i = 0; i < a_count; i++ ) {
            atoms[i]->turn();
        }
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


#include "printing.cpp"