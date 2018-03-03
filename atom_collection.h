#pragma once

#include "atom.cpp"
#include "helpers.cpp"

struct AtomCollection {
    SList<Atom*> list;
    Atom ** atoms() { return list.source(); }

    ~AtomCollection() { // should not destruct this
        // std::cout << "AtomCollection destructed" << std::endl;
        // for (int i = 0; i < a_count; i++) {
        //     delete atoms[i];
        // }
        // delete[] atoms;
    }
};
