/* 
 * File:   filters.h
 * Author: filip
 *
 * Created on May 3, 2014, 2:22 PM
 */

#ifndef CPUFILTER_H
#define	CPUFILTER_H

#include "main.h"

#include <ImfArray.h>
#include <ImfRgba.h>

using namespace Imf;

void
cpu_filter
(
        Array2D<Rgba> &pixels,
        int width,
        int height,
        t_times &time
);

#endif	/* CPU_FILTER_H */

