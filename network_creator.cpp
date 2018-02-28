#pragma once

#include <functional>
#include "atom.cpp"

class NCreator {
public:
    virtual AtomIParams gen_rand() = 0;

    const Network& create_random_network(int size) {
        Network * re = new Network{};
        re->atoms = new Atom*[size];

        for (int i = 0; i < size; i++) {
            re->atoms[i] = new Atom( this->gen_rand()  );
        }

        return *re;
    }
};

