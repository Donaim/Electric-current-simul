#pragma once

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
    NCreatorParams(Shape& _sh) : sh(_sh) {}

    virtual ~NCreatorParams() {}
};

template< typename SH_T >
struct DensityParams : NCreatorParams {
    const SH_T sh_t;
    DensityParams(SH_T& sh) : NCreatorParams(sh), sh_t(sh) {}
    float density;
};