#pragma once

#include "atom.cpp"
#include <iostream>
#include <functional>

struct Network;
typedef std::function<void(Network*)> nconnector_t;

struct Network {
    Atom ** atoms = nullptr;
    int a_count = 0;
};

#define MAX_CONNECTION_DIST 1.0f

class ConnectedNetwork : protected Network {
public:
    ConnectedNetwork(Network& init, nconnector_t connector_method) : Network(init) {
        connector_method(this);
    }
    void lap() {
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