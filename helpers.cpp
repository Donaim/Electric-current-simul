#pragma once

inline float pow2(float x) { return x * x; }

template <typename T>
T * create_arr(T * source, int size) {
    T * re = new T[size];
    for (int i = 0; i < size; i++ ){ 
        re[i] = source[i];
    }
    return re;
}