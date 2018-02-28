#pragma once

#include "rng.cpp"
#include "helpers.cpp"
#include <stdint.h>
#include <cmath>
#include <iostream>

using std::ostream;

struct AtomIParams {
    int protons;
    int electrons;
    int free_space;
    float x, y;
};

    // dont want to create Electron class, it would be too much.. 
class Atom {
    static inline int get_d_value(const Atom & a, int min) { return a.charge() - min; } // this scales charges between 0 and max 
    static inline int get_min_d_value(Atom ** const atoms, int n, const Atom & me) {
        int m = INT32_MAX;
        for (int i = 0; i < n; i++) {
            Atom &a = (*atoms[i]);
            if (a.free_space < 1) { continue; }
            if (a.charge() < m) { m = a.charge(); }
        }
        if (me.charge() < m) { m = me.charge(); } // origin atom also counts
        return m;
    }
    static inline int get_d_value_sum(Atom ** const atoms, int n, int min, const Atom & me) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            Atom &a = (*atoms[i]);
            if (a.free_space < 1) { continue; }
            sum += Atom::get_d_value(a, min);
        }
        sum += Atom::get_d_value(me, min); // origin atom also counts
        return sum;
    }
    static inline void move_electron_s(Atom& sender, Atom& reciever) {
        sender.electrons--;
        reciever.electrons++; // so the actual movement looks like this... 
        reciever.free_space--;
        if (sender.free_space < sender.max_free_space) { sender.free_space++; }
    }
    void move_electron(int d_rand, int min) {
        int sum = 0;
        for (int i = 0; i < n_count; i++) {
            Atom &a = (*neighbors[i]);
            if (a.free_space < 1) { continue; }

            sum += Atom::get_d_value(a, min);
            if (sum >= d_rand) 
            {
                move_electron_s(*this, a);
                return;
            }
        }
        // there is a probability, that electron will stay home. that is because we have added home's d_value to the sum, and therefore it is greather than the sum of only neighboring atoms
    }
    void share_electron() {
        int min = Atom::get_min_d_value(neighbors, n_count, *this);
        int sum = Atom::get_d_value_sum(neighbors, n_count, min, *this);

        int r = rand_0_max(sum); 
        move_electron(r, min); // direction is chosen based on random waged distribution
    }
public:
    Atom ** neighbors = nullptr; // adresses of neighbor atoms. it's with them electron exchange is happening
    int n_count = 0;

    // float acceptance = 1.0f; // represents 'will' to accept new electrons. the lower this value is, the less probable it is for atom to accept new electrons
    int free_space; // primitive alternative to 'acceptance'. probability of acceptance here is 0% if free_space == 0, or 100% if free_space > 0
    const int max_free_space;

    const int protons;
    int electrons;
    inline int charge() const { return +protons -electrons; }

    const float x, y; // physical position of atom in 2d space

    void turn() { // make a turn, or pass
        for (int c = charge(); c < 0; c++) { // if there is excess of electrons, they move to atom which has less of them
            share_electron();
        }
    }

public:
    Atom(AtomIParams p) : protons(p.protons), electrons(p.electrons), max_free_space(p.free_space), free_space(p.free_space), x(p.x), y(p.y) {}
    ~Atom();
    friend ostream& operator << (ostream& os, const Atom& o);
};



class Network {
public:
    Atom ** atoms = nullptr;
    int a_count = 0;
    void lap() {
        for (int i = 0; i < a_count; i++ ) {
            atoms[i]->turn();
        }
    }

    static inline float dist2(Atom * a, Atom * b) { return pow2(a->x - b->x) + pow2(a->y - b->y); } // distance squared
    ~Network();
    friend ostream& operator << (ostream& os, const Network& o);
};


ostream& operator << (ostream& os, const Atom& o){
    os << "O" ;
    return os;
}

ostream& operator << (ostream& os, const Network& o){
    for (int i = 0; i < o.a_count; i++) {
        os << *o.atoms[i] << ' ';
    }
    return os;
}

Atom::~Atom() {
    // std::cout << "DS ATOM!" << std::endl;
    delete[] neighbors;
}
Network::~Network() {
    // std::cout << "destructed " << a_count << " atoms" << std::endl;
    for (int i = 0; i < a_count; i++ ){
        delete atoms[i];
    }
    delete[] atoms;
}