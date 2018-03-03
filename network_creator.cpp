#pragma once

#include "atom.cpp"
#include "network.cpp"
#include "rng.cpp"
#include "network_creator_params.cpp"
#include <stdexcept>

class NCreator {
protected:
    SList<Atom*> collection;
    NCreator() : collection{1000} {}
public:
    virtual AtomBase gen_rand(NCreatorParams& p) = 0;
    virtual void add_part(NCreatorParams& p) = 0;

    ConnectedNetwork& finish(NCreatorParams& p) {
        AtomCollection init{};
        init.atoms = collection.source();
        init.a_count = collection.size();
        ConnectedNetwork& re = p.nconstructor.construct(init, p);

        collection.forget_and_alloc_new(10);
        
        return re;
    }

    ConnectedNetwork& create_solid_random_network(NCreatorParams& p) {
        this->add_part(p);
        return this->finish(p);
    }
};

class SimpleCreator : public NCreator {
public:
    int protons_avg = 5;
    int protons_dev = 1;
    int electrons_dev = 3;
    int free_space_max = 10;
    

    virtual void add_part(NCreatorParams& p) {
        DensityParams * pt = dynamic_cast<DensityParams * >(&p);
        if (!pt) { throw std::runtime_error("Simple creator accepts only DensityParams"); }

        int size = p.sh.area() * pt->density;
        for (int i = 0; i < size; i++) {
            collection.push_back(new Atom( gen_rand(p) ));
        }
    }
    virtual AtomBase gen_rand(NCreatorParams& p) override {
        const RectangleF * sh = dynamic_cast<const RectangleF * >(&(p.sh));
        if (!sh) { throw std::runtime_error("Simple creator accepts only RectangleF"); }
        
        auto working_rec = *sh;
        AtomBase re{};

        re.x = rand_min_max(working_rec.x, working_rec.x + working_rec.Width);
        re.y = rand_min_max(working_rec.y, working_rec.y + working_rec.Height);

        re.protons      = rand_i_min_max(protons_avg - protons_dev  , protons_avg + protons_dev  );
        re.electrons    = rand_i_min_max(protons_avg - electrons_dev, protons_avg + electrons_dev);
        
        re.max_free_space = re.free_space = rand_i_0_max(free_space_max);

        return re;
    }
    
};