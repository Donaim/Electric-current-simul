#pragma once

#include "atom.cpp"
#include "rng.cpp"
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <iostream> 

struct Shape { 
    virtual float area() const = 0;
};
struct RectangleF : public Shape {
    float x; float y;
    float Width; float Height;
    RectangleF(float _x, float _y, float _Width, float _Height) : x{_x}, y{_y}, Width{_Width}, Height{_Height} {}

    virtual float area() const override { return Width * Height; }
};



class NCreator {
    SList<Atom*> collection;
protected:
    NCreator() : collection{1000} {}

    virtual void connect_network(Network * net) {
        int n = net->a_count;
        Atom ** arr = net->atoms;
        float dist = pow2(max_connection_dist);

        float avg_neighbors = 10; // helps with allocation
        SList<Atom*> list(avg_neighbors);

        for (int x = 0; x < n; x++ ) {
            Atom * tmp = arr[x];
            list.forget_and_alloc_new((int)avg_neighbors + 17);
   
            for (int y = 0; y < n; y++) {
                if (Network::dist2(tmp, arr[y]) < dist) {
                    list.push_back(arr[y]);
                }
            }
   
            tmp->neighbors = list.source();
            tmp->n_count = list.size();
            avg_neighbors = (avg_neighbors * (x) + list.size()) / (float)(x + 1);
            
        }
        
        std::cout << "avg network connections: " << avg_neighbors << std::endl;
    }
public:
    float max_connection_dist = 10;
public:
    virtual AtomIParams gen_rand(Shape&) = 0;
    void add_part(Shape & sh, int size) {
        for (int i = 0; i < size; i++) {
            collection.push_back(new Atom( gen_rand(sh) ));
        }
    }
    Network& finish() {
        Network * re = new Network{};
        re->atoms = collection.source();
        re->a_count = collection.size();
        connect_network(re);

        collection.forget_and_alloc_new(10);
        
        return *re;
    }
    Network& create_solid_random_network(Shape& sh, int size) {
        this->add_part(sh, size);
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