#pragma once

#include "atom.cpp"
#include "network.cpp"

using std::ostream;

ostream& operator << (ostream& os, const Atom& o){
    os << "O" ;
    return os;
}

ostream& operator << (ostream& os, const ConnectedNetwork& o){
    for (int i = 0; i < o.a_count; i++) {
        os << *o.atoms[i] << ' ';
    }
    return os;
}
