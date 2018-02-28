#pragma once

#include "atom.cpp"
#include "rng.cpp"
#include <vector>
#include <stdexcept>

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
    std::vector<Atom*> collection;
protected:
    virtual void connect_network(Network * net) {
        int n = net->a_count;
        Atom ** arr = net->atoms;
        float dist = pow2(max_connection_dist);

        for (int x = 0; x < n; x++ ) {
            Atom * tmp = arr[x];
            tmp->neighbors = new Atom*[n];
            int n_count = 0;
   
            for (int y = x; y < n; y++) {
                if (Network::dist2(tmp, arr[y]) < dist) {
                    tmp->neighbors[n_count++] = arr[y];
                }
            }
   
            tmp->n_count = n_count;
        }
    }
public:
    float max_connection_dist = 10;
public:
    virtual AtomIParams gen_rand(Shape&) = 0;
    void add_part(int size, Shape & sh) {
        for (int i = 0; i < size; i++) {
            collection.push_back(new Atom( gen_rand(sh) ));
        }
    }
    Network& finish() {
        Network * re = new Network{};
        re->atoms = &collection[0];
        re->a_count = collection.size();
        connect_network(re);

        collection = std::vector<Atom*>{}; // dont care about memory
        
        return *re;
    }
public:
    static Network& create_solid_random_network(NCreator& creator, Shape& sh, int size) {
        Network * re = new Network{};
        re->atoms = new Atom*[size];

        for (int i = 0; i < size; i++) {
            re->atoms[i] = new Atom( creator.gen_rand(sh)  );
        }
        creator.connect_network(re);
        
        return *re;
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