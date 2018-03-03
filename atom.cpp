#pragma once

#include "rng.cpp"
#include "helpers.cpp"
#include <stdint.h>
#include <iostream>

struct AtomBase {
    int protons;
    int electrons;
    inline int charge() const { return +protons -electrons; }

    // float acceptance = 1.0f; // represents 'will' to accept new electrons. the lower this value is, the less probable it is for atom to accept new electrons
    int free_space; // primitive alternative to 'acceptance'. probability of acceptance here is 0% if free_space == 0, or 100% if free_space > 0
    int max_free_space;

    float x, y;
};

    // dont want to create Electron class, it would be too much.. 
class Atom : public AtomBase {
    static inline int get_d_value(const AtomBase & a, int min) { return a.charge() - min; } // this scales charges between 0 and max 
    static inline int get_min_d_value(Atom ** atoms, int n, const Atom & me) {
        int m = INT32_MAX;
        for (int i = 0; i < n; i++) {
            const AtomBase &a = (*atoms[i]);
            if (a.free_space < 1) { continue; }
            if (a.charge() < m) { m = a.charge(); }
        }
        if (me.charge() < m) { m = me.charge(); } // origin atom also counts
        return m;
    }
    static inline int get_d_value_sum(Atom ** atoms, int n, int min, const AtomBase & me) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            const AtomBase &a = (*atoms[i]);
            if (a.free_space < 1) { continue; }
            sum += Atom::get_d_value(a, min);
        }
        sum += Atom::get_d_value(me, min); // origin atom also counts
        return sum;
    }
    static inline void exchange_e(AtomBase& sender, AtomBase& reciever) {
        sender.electrons--;
        reciever.electrons++; // so the actual movement looks like this... 
        reciever.free_space--;
        if (sender.free_space < sender.max_free_space) { sender.free_space++; }
    }
    Atom& choose_winner(int d_rand, int min) {
        int sum = 0;
        for (int i = 0; i < n_count; i++) {
            Atom &a = (*neighbors[i]);
            if (a.free_space < 1) { continue; }

            sum += Atom::get_d_value(a, min);
            if (sum >= d_rand) { return a; }
        }
        return *this;
        // there is a probability, that electron will stay home. that is because we have added home's d_value to the sum, and therefore it is greather than the sum of only neighboring atoms
    }
    void share_electron() {
        int min = Atom::get_min_d_value(neighbors, n_count, *this);
        int sum = Atom::get_d_value_sum(neighbors, n_count, min, *this);

        int r = rand_0_max(sum); 
        Atom& winner = choose_winner(r, min); // direction is chosen based on random waged distribution
        exchange_e(*this, winner);
    }
public:
    Atom ** neighbors = nullptr; // adresses of neighbor atoms. it's with them electron exchange is happening
    int n_count = 0;
    virtual void turn() { // make a turn, or pass
        for (int c = charge(); c < 0; c++) { // if there is excess of electrons, they move to atom which has less of them
            share_electron();
        }
    }

public:
    static inline float dist2(AtomBase * a, AtomBase * b) { return pow2(a->x - b->x) + pow2(a->y - b->y); } // distance squared
    Atom(AtomBase b) : AtomBase(b) {}
    ~Atom();
    friend std::ostream& operator << (std::ostream& os, const Atom& o);
};


Atom::~Atom() {
    // std::cout << "DS ATOM!" << std::endl;
    delete[] neighbors;
}

#include <iostream>
using std::ostream;

ostream& operator << (ostream& os, const Atom& o){
    if (o.charge() < 0) 
    { os << '-'; }
    else 
    { os << '+';}

    os << '(' << absi(o.charge()) << ')';

    return os;
}
