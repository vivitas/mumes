/* 
 * File:   open_exr_io.h
 * Author: filip
 *
 * Created on May 3, 2014, 2:03 PM
 */

#ifndef OPENEXRIO_H
#define	OPENEXRIO_H

#include <ImfRgba.h>
#include <ImfArray.h>

using namespace Imf;

void
writeRgba1
(
        const char fileName[],
        const Rgba *pixels,
        int width,
        int height
);

void
readRgba1
(
        const char fileName[],
        Array2D<Rgba> &pixels,
        int &width,
        int &height
);

#endif	/* OPENEXRIO_H */

