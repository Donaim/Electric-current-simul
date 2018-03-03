#pragma once
// #include "network.cpp"
#include "helpers.cpp"
#include "nconnectors.h"

struct Shape { 
    virtual float area() const = 0;
};

struct RectangleF : public Shape {
    float x; float y;
    float Width; float Height;
    RectangleF(float _x, float _y, float _Width, float _Height) : x{_x}, y{_y}, Width{_Width}, Height{_Height} {}

    virtual float area() const override { return Width * Height; }
};

class ConnectedNetwork;
class AtomCollection;
struct NCreatorParams;
struct NetworkConstructor {
    virtual ConnectedNetwork& construct(AtomCollection& base, const NCreatorParams& p) const = 0;
};

struct NCreatorParams {
    const Shape& sh;
    const Connector& connector;
    const NetworkConstructor& nconstructor;
    NCreatorParams(const Shape& _sh, const Connector& c, const NetworkConstructor& nc) 
        : sh(_sh), connector(c), nconstructor(nc) {}

    virtual ~NCreatorParams() {}
};

struct DensityParams : NCreatorParams {
    DensityParams(const Shape& sh, const Connector& c, const NetworkConstructor& nc, float density) 
        : NCreatorParams(sh, c, nc), density(density) {}
    float density;
};
