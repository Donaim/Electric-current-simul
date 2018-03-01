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
    DensityParams(const Shape& sh, const Connector& c, float density) : NCreatorParams(sh, c), density(density) {}
    float density;
};
