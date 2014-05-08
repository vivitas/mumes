#include "common.h"
t_RGBA
cpu_avg_from_to
(
t_RGBA *data,
int x_from,
int x_to,
int y_from,
int y_to,
int z,
int width,
int height,
int depth
);
void
cpu_filter
(
t_RGBA *raw,
int width,
int height,
int depth
);