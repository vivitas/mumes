/* 
 * File:   my_hdr_io.h
 * Author: filip
 *
 * Created on May 4, 2014, 3:52 PM
 */

#ifndef MY_HDR_IO_H
#define	MY_HDR_IO_H

#include "common_filter.h"

void
write_my_hdr
(
        const char* output_file_name,
        t_my_rgba *pixels,
        int width,
        int height
);

void
read_my_hdr
(
        const char* input_file_name,
        t_my_rgba **raw_pixels,
        int &width,
        int &height
);

#endif	/* MY_HDR_IO_H */

