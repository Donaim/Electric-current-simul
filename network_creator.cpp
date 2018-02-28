#pragma once

#include "atom.cpp"
#include "rng.cpp"
#include <vector>

struct RectangleF {
    float x, y;
    float Width, Height;
};

class NCreator {
    std::vector<Atom*> collection;
public:
    const RectangleF working_rec;
    virtual AtomIParams gen_rand() = 0;
    virtual void add_part(int size) {
        for (int i = 0; i < size; i++) {
            collection.push_back(new Atom( gen_rand() ));
        }
    }
    virtual Network finish() {
        Network * re = new Network{};
        re->atoms = &collection[0];
        re->a_count = collection.size();

        collection = std::vector<Atom*>{}; // dont care about memory
        
        return *re;
    }

    static Network create_solid_random_network(NCreator& creator, int size) {
        Network * re = new Network{};
        re->atoms = new Atom*[size];

        for (int i = 0; i < size; i++) {
            re->atoms[i] = new Atom( creator.gen_rand()  );
        }

        return *re;
    }
};

class SimpleCreator : public NCreator {
public:
    int protons_avg = 5;
    int protons_dev = 1;
    int electrons_dev = 3;
    int free_space_max = 10;

    virtual AtomIParams gen_rand() {
        AtomIParams re{};

        re.x = rand_min_max(working_rec.x, working_rec.x + working_rec.Width);
        re.y = rand_min_max(working_rec.y, working_rec.y + working_rec.Height);

        re.protons      = rand_i_min_max(protons_avg - protons_dev  , protons_avg + protons_dev  );
        re.electrons    = rand_i_min_max(protons_avg - electrons_dev, protons_avg + electrons_dev);
        
        re.free_space = rand_i_0_max(free_space_max);

        return re;
    }
};