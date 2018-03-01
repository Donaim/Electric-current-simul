#pragma once
#include "network.cpp"

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
    const nconnector_t connector;
    NCreatorParams(Shape& _sh, nconnector_t c) : sh(_sh), connector(c) {}

    virtual ~NCreatorParams() {}
};

struct DensityParams : NCreatorParams {
    DensityParams(Shape& sh, nconnector_t c) : NCreatorParams(sh, c) {}
    float density;
};