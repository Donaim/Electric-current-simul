#pragma once
#include "network.cpp"
#include "helpers.cpp"

struct Shape { 
    virtual float area() const = 0;
};

struct RectangleF : public Shape {
    float x; float y;
    float Width; float Height;
    RectangleF(float _x, float _y, float _Width, float _Height) : x{_x}, y{_y}, Width{_Width}, Height{_Height} {}

    virtual float area() const override { return Width * Height; }
};


struct NCreatorParams {
    const Shape& sh;
    const Connector& connector;
    NCreatorParams(const Shape& _sh, const Connector& c) : sh(_sh), connector(c) {}

    virtual ~NCreatorParams() {}
};

struct DensityParams : NCreatorParams {
    DensityParams(const Shape& sh, const Connector& c) : NCreatorParams(sh, c) {}
    float density;
};

namespace connectors {
    struct Intuitive : Connector {
        virtual Atom ** connect(const Network& net) const override {
            AtomBase ** arr = net.atoms;
            int n = net.a_count;
            float dist = pow2(MAX_CONNECTION_DIST);
            Atom ** re = new Atom*[n];

            float avg_neighbors = 10; // helps with allocation
            SList<AtomBase*> list(avg_neighbors);

            for (int x = 0; x < n; x++ ) {
                AtomBase * tmp = arr[x];
                list.forget_and_alloc_new((int)avg_neighbors + 17);
    
                for (int y = 0; y < n; y++) {
                    if (Atom::dist2(tmp, arr[y]) < dist) {
                        list.push_back(arr[y]);
                    }
                }

                re[x] = new Atom(*tmp, list.source(), list.size());
                avg_neighbors = (avg_neighbors * (x) + list.size()) / (float)(x + 1);
            }
            
            std::cout << "avg network connections: " << avg_neighbors << std::endl;

            return re;
        }
    };
}