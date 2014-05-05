#include "common_filter.h"
#include "stdlib.h"

void
alloc_buffers
(
        t_my_rgba* &input_buffer,
        t_my_rgba* &output_buffer,
        int width,
        int height
)
{
    input_buffer = (t_my_rgba*)malloc(width*height*sizeof(t_my_rgba));
    output_buffer = (t_my_rgba*)malloc(width*height*sizeof(t_my_rgba));
}
t_my_rgba
to_my_rgba
(
        Rgba& src
)
{
    t_my_rgba dest;
    dest.a = (float) src.a;
    dest.r = src.r.operator  float();
    dest.g = src.g.operator  float();
    dest.b = src.b.operator  float();
    return dest;
}
Rgba
from_my_rgba
(
        t_my_rgba &src
)
{
	Rgba result(half(src.r), half(src.g), half(src.b), half(src.a));
    return result;
}

t_my_rgba
divide
(
        t_my_rgba& pixel,
        float coef
)
{
    t_my_rgba result;
    result.a = pixel.a/coef;
    result.r = pixel.r/coef;
    result.g = pixel.g/coef;
    result.b = pixel.b/coef;
    return result;
}

t_my_rgba&
increment
(
        t_my_rgba& dst,
        t_my_rgba src
)
{
    dst.a += src.a;
    dst.r += src.r;
    dst.g += src.g;
    dst.b += src.b;
    return dst;
}
void
copy
(
        t_my_rgba *dest,
        Array2D<Rgba> &src,
        int width,
        int height
)
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            dest[y*width + x] = to_my_rgba(src[y][x]);            
}
void
copy
(
        Array2D<Rgba> &dest,
        t_my_rgba *src,
        int width,
        int height
)
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            dest[y][x] = from_my_rgba(src[y*width + x]);
}
void
free_buffers
(
        t_my_rgba *input,
        t_my_rgba *output
)
{
    free(input);
    free(output);
}