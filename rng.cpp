#pragma once

#include <stdlib.h>

inline float rand_min_max(float min, float max) { return (rand() / (float)RAND_MAX) * (max - min) + min; }
inline float rand_0_max(float max) { return rand_min_max(0, max); }

inline float rand_i_min_max(int min, int max) { return (rand() / (float)RAND_MAX) * ((max + 1) - min) + min; }
inline float rand_i_0_max(int max) { return rand_i_min_max(0, max); }