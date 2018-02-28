#pragma once

#include <stdlib.h>

inline float pow2(float x) { return x * x; }
inline int absi(int x) { return x < 0 ? -x : x; }

template <typename T>
T * create_arr(T * source, int size) {
    T * re = new T[size];
    for (int i = 0; i < size; i++ ){ 
        re[i] = source[i];
    }
    return re;
}

template <typename T>
class SList { // simple list. no checks, no safety. only special-case use
    T * buffer;
    int _size;
    int _capacity;
public:
    SList(int capac_init) {
        forget_and_alloc_new(capac_init);
    }
    inline void forget_and_alloc_new(unsigned int capac_init) {
        _capacity = capac_init;
        buffer = (T*) malloc (sizeof(T) * _capacity);
        _size = 0;
    }

    inline void push_back(const T & v) {
        if (_size >= _capacity) {
            reserve(_capacity * 2);
        }
        buffer [_size++] = v;
    }

    inline void reserve(unsigned int capacity) {
        _capacity = capacity;
        buffer = (T*)realloc(buffer, sizeof(T) * capacity);
    }
    inline T * source() { return buffer; }
    inline int size() { return _size; }
};
