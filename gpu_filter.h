/* 
 * File:   gpu_filter.h
 * Author: filip
 *
 * Created on May 3, 2014, 8:01 PM
 */

#ifndef GPU_FILTER_H
#define	GPU_FILTER_H

#include "main.h"
#include "common_filter.h"

void
gpu_filter
(
        Array2D<Rgba> &pixels,
        int width,
        int height,
        t_times &time
);


#endif	/* GPU_FILTER_H */

