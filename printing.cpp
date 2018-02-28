#pragma once

#include "atom.cpp"
#include "network.cpp"
#include "helpers.cpp"

using std::ostream;

ostream& operator << (ostream& os, const Atom& o){
    if (o.charge() < 0) 
    { os << '-'; }
    else 
    { os << '+';}

    os << '(' << absi(o.charge()) << ')';

    return os;
}

ostream& operator << (ostream& os, const ConnectedNetwork& o){
    for (int i = 0; i < o.a_count; i++) {
        os << *o.atoms[i] << ' ';
    }
    return os;
}
