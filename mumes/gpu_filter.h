#include "common.h"
#include "cuda.h"
t_timing
gpu_filter
(
    t_RGBA *&raw,
    int width,
    int height,
    int depth,
    int repetitions = 1
);