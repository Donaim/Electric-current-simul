#pragma once

#include <stdlib.h>

inline float rand_min_max(float min, float max) { return (rand() / (float)RAND_MAX) * (max - min) + min; }
inline float rand_0_max(float max) { return rand_min_max(0, max); }