/* 
 * File:   common_filter.h
 * Author: filip
 *
 * Created on May 3, 2014, 7:25 PM
 */

#ifndef COMMON_FILTER_H
#define	COMMON_FILTER_H

#include "ImfRgba.h"
#include "ImfArray.h"

using namespace Imf;

struct t_my_rgba
{
    float r;
    float g;
    float b;
    float a;
};
t_my_rgba
to_my_rgba
(
        Rgba& src
);
Rgba
from_my_rgba
(
        t_my_rgba &src
);
t_my_rgba
divide
(
        t_my_rgba& pixel,
        float coef
);
t_my_rgba&
increment
(
        t_my_rgba& dst,
        t_my_rgba src
);
void
copy
(
        t_my_rgba *dest,
        Array2D<Rgba> &src,
        int width,
        int height
);
void
copy
(
        Array2D<Rgba> &dest,
        t_my_rgba *src,
        int width,
        int height
);
void
alloc_buffers
(
        t_my_rgba* &input_buffer,
        t_my_rgba* &output_buffer,
        int width,
        int height
);
void
free_buffers
(
        t_my_rgba *input,
        t_my_rgba *output
);
#endif	/* COMMON_FILTER_H */

