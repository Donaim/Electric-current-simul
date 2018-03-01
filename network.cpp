#pragma once

#include "atom.cpp"
#include <iostream>
#include <functional>

class Network;
typedef std::function<void(Network*)> nconnector_t;

class Network {
public:
    Atom ** atoms = nullptr;
    int a_count = 0;
    static inline float dist2(Atom * a, Atom * b) { return pow2(a->x - b->x) + pow2(a->y - b->y); } // distance squared
};

#define MAX_CONNECTION_DIST 1.0f

class ConnectedNetwork : protected Network {
public:
    static void connect_me(Network * net) {
        int n = net->a_count;
        Atom ** arr = net->atoms;
        float dist = pow2(MAX_CONNECTION_DIST);

        float avg_neighbors = 10; // helps with allocation
        SList<Atom*> list(avg_neighbors);

        for (int x = 0; x < n; x++ ) {
            Atom * tmp = arr[x];
            list.forget_and_alloc_new((int)avg_neighbors + 17);
   
            for (int y = 0; y < n; y++) {
                if (Network::dist2(tmp, arr[y]) < dist) {
                    list.push_back(arr[y]);
                }
            }
   
            tmp->neighbors = list.source();
            tmp->n_count = list.size();
            avg_neighbors = (avg_neighbors * (x) + list.size()) / (float)(x + 1);
            
        }
        
        std::cout << "avg network connections: " << avg_neighbors << std::endl;
    }
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