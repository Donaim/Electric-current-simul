#pragma once

#include "atom.cpp"
#include "network.cpp"
#include "rng.cpp"
#include "network_creator_params.cpp"
#include <stdexcept>
#include <type_traits>

#define __NCREATOR_INHERIT(x, y) public NCreator< x<y>, y >

template <typename T, typename SH_T>
class NCreator {
    static_assert(std::is_base_of<NCreatorParams<SH_T>, T>::value, "T must inherit from NCreatorParams!");
protected:
    SList<Atom*> collection;
    NCreator() : collection{1000} {}
public:
    virtual AtomBase gen_rand(T&) = 0;
    virtual void add_part(T& p) = 0;
    ConnectedNetwork& finish() {
        Network init{};
        init.atoms = collection.source();
        init.a_count = collection.size();
        ConnectedNetwork * re = new ConnectedNetwork{init};

        collection.forget_and_alloc_new(10);
        
        return *re;
    }
    ConnectedNetwork& create_solid_random_network(T& p) {
        this->add_part(p);
        return this->finish();
    }
};

class SimpleCreator : __NCREATOR_INHERIT(DensityParams, RectangleF) {
public:
    int protons_avg = 5;
    int protons_dev = 1;
    int electrons_dev = 3;
    int free_space_max = 10;
    
    virtual void add_part(DensityParams<RectangleF>& p) {
        int size = p.sh.area() * p.density;
        for (int i = 0; i < size; i++) {
            collection.push_back(new Atom( gen_rand(p) ));
        }
    }
    virtual AtomBase gen_rand(DensityParams<RectangleF>& sh) override {
        auto working_rec = sh.sh;
        AtomBase re{};

        re.x = rand_min_max(working_rec.x, working_rec.x + working_rec.Width);
        re.y = rand_min_max(working_rec.y, working_rec.y + working_rec.Height);

        re.protons      = rand_i_min_max(protons_avg - protons_dev  , protons_avg + protons_dev  );
        re.electrons    = rand_i_min_max(protons_avg - electrons_dev, protons_avg + electrons_dev);
        
        re.max_free_space = re.free_space = rand_i_0_max(free_space_max);

        return re;
    }
};