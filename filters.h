/* 
 * File:   filters.h
 * Author: filip
 *
 * Created on May 3, 2014, 2:22 PM
 */

#ifndef FILTERS_H
#define	FILTERS_H

#include <ImfArray.h>
#include <ImfRgba.h>

struct t_times
{
    int transfer_to;
    int processing;
    int transfer_from;
};

using namespace Imf;

Array2D<Rgba>
cpu_filter
(
        Array2D<Rgba> &pixels, 
        int width,
        int height,
        t_times &time
);

#endif	/* FILTERS_H */

