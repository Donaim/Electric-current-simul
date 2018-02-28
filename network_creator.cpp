#pragma once

#include "atom.cpp"
#include "rng.cpp"
#include "network_creator_shapes.cpp"
#include <stdexcept>

class NCreator {
    SList<Atom*> collection;
protected:
    NCreator() : collection{1000} {}
public:
    virtual AtomIParams gen_rand(Shape&) = 0;
    void add_part(Shape & sh, float density) {
        int size = sh.area() * density;
        for (int i = 0; i < size; i++) {
            collection.push_back(new Atom( gen_rand(sh) ));
        }
    }
    ConnectedNetwork& finish() {
        Network init{};
        init.atoms = collection.source();
        init.a_count = collection.size();
        ConnectedNetwork * re = new ConnectedNetwork{init};

        collection.forget_and_alloc_new(10);
        
        return *re;
    }
    ConnectedNetwork& create_solid_random_network(Shape& sh, float density) {
        this->add_part(sh, density);
        return this->finish();
    }
};

class SimpleCreator : public NCreator {
public:
    int protons_avg = 5;
    int protons_dev = 1;
    int electrons_dev = 3;
    int free_space_max = 10;

    virtual AtomIParams gen_rand(Shape& sh) {
        const RectangleF* working_rec = dynamic_cast<const RectangleF*>(&sh);
        if(!working_rec) { throw std::runtime_error("Dont know how to handle this shape"); } 

        AtomIParams re{};

        re.x = rand_min_max(working_rec->x, working_rec->x + working_rec->Width);
        re.y = rand_min_max(working_rec->y, working_rec->y + working_rec->Height);

        re.protons      = rand_i_min_max(protons_avg - protons_dev  , protons_avg + protons_dev  );
        re.electrons    = rand_i_min_max(protons_avg - electrons_dev, protons_avg + electrons_dev);
        
        re.free_space = rand_i_0_max(free_space_max);

        return re;
    }
};