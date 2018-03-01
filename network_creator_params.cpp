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


template <typename SH_T>
struct NCreatorParams {
    static_assert(std::is_base_of<Shape, SH_T>::value, "SH_T must inherit from Shape!");
    
    const SH_T& sh;
    NCreatorParams(SH_T& _sh) : sh(_sh) {}

    virtual ~NCreatorParams() {}
};

template <typename SH_T>
struct DensityParams : NCreatorParams<SH_T> {
    DensityParams(SH_T& sh) : NCreatorParams<SH_T>(sh) {}
    float density;
};