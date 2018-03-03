#pragma once

#include "atom.cpp"

struct AtomCollection {
    Atom ** atoms;
    int a_count;
    ~AtomCollection() { // should not destruct this
        // std::cout << "AtomCollection destructed" << std::endl;
        // for (int i = 0; i < a_count; i++) {
        //     delete atoms[i];
        // }
        // delete[] atoms;
    }
};
