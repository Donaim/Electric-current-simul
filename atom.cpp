
#include <stdint.h>
#include "rng.cpp"

    // dont want to create Electron class, it would be too much.. 
class Atom {
    static inline int get_d_value(const Atom & a, int min) { return a.charge() + min; } 
    static inline int get_min_d_value(Atom ** const atoms, int n) {
        int m = INT32_MAX;
        for (int i = 0; i < n; i++) {
            Atom &a = (*atoms[i]);
            if (a.free_space < 1) { continue; }
            if (a.charge() < m) { m = a.charge(); }
        }
        return m;
    }
    static inline int get_d_value_sum(Atom ** const atoms, int n, int min) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            Atom &a = (*atoms[i]);
            if (a.free_space < 1) {continue; }
            sum += Atom::get_d_value(a, min);
        }
        return sum;
    }
    
    void share_electron() {
        int min = Atom::get_min_d_value(neighbors, n_count);
        int sum = Atom::get_d_value_sum(neighbors, n_count, min);
        // float r = rand_0_max()

    }
public:
    Atom ** neighbors = nullptr; // adresses of neighbor atoms. its with them electrons exchange is happening
    int n_count = 0;

    // float acceptance = 1.0f; // represents 'will' to accept new electrons. the lower this value is, the less probable it is for atom to accept new electrons
    int free_space = 0; // primitive alternative to 'acceptance'. probability of acceptance is here is 0% if free_space == 0, or 100% if free_space > 0
    
    int protons = 0;
    int electrons = 0;
    inline int charge() const { return protons - electrons; }

    float x = -1, y = -1;

    void turn() { // make a turn, or pass
        for (int c = charge(); c < 0; c++) { // if there is excess of electrons, they move to atom which has less of them
            share_electron();
        }
    }

    ~Atom();
};


class Network {
public:
    Atom * atoms = nullptr;
    int a_count = 0;

    ~Network();
};


Atom::~Atom() {
    delete[] neighbors;
}
Network::~Network() {
    delete[] atoms;
}