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

struct DensityParams : NCreatorParams {
    DensityParams(Shape& sh) : NCreatorParams(sh) {}
    float density;
};