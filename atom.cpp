


    // dont want to create Electron class, it would be too much.. 
class Atom {
    float get_average_neighbors() {
        int sum = 0;
        for (int i = 0; i < n_count; i++) {
            sum += neighbors[i].charge();
        }
        return sum / (float)n_count;
    }
    void share_electrons() {

    }
public:
    Atom * neighbors = nullptr;
    int n_count = 0;

    int free_space = 0;
    int protons = 0;
    int electrons = 0;
    inline int charge() { return protons - electrons; }

    float x = -1, y = -1;

    void turn() { // make a turn, or pass
        if (electrons > protons) { share_electrons(); } // if there is excess of electrons, they move to atom which has little of them
        float avg = get_average_neighbors();

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