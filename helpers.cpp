#pragma once

inline float pow2(float x) { return x * x; }

template<class T, class Z>
T ToType(const Z ptr)
{
    return dynamic_cast<const T>(ptr);
}