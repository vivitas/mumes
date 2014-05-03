#include <OpenEXR/half.h>

#include "common_filter.h"
#include "cpu_filter.h"
#include "stdlib.h"

#include "ScopeClock.h"

t_my_rgba
cpu_middle_filter
(
        t_my_rgba* start,
        int x,
        int y,
        int width
)
{
    t_my_rgba result;
    result.a = 0;
    result.r = 0;
    result.g = 0;
    result.b = 0;
    for (int dx = -1; dx<2; ++dx)
        for (int dy = -1; dy<2; ++dy)
        {
            increment(result, divide (start[(y+dy)*width + x+dx], 9.f));
        }
    return result;
}

t_my_rgba
cpu_y_edge_filter
(
        t_my_rgba *start,
        int x,
        int y,
        int y_direction,
        int width
)
{
    t_my_rgba result;
    result.a = 0;
    result.r = 0;
    result.g = 0;
    result.b = 0;
    for (int dx = -1; dx<2; ++dx)
        for (int coef_y = 0; coef_y <=1; ++coef_y)
        {
            int true_y = y+y_direction*coef_y;
            int true_x = x+dx;
            increment(result, divide(start[true_y*width + true_x], 6.f));            
        }
    return result;
}
t_my_rgba
cpu_x_edge_filter
(
        t_my_rgba *start,
        int x,
        int y,
        int x_direction,
        int width
)
{
    t_my_rgba result;
    result.a = 0;
    result.r = 0;
    result.g = 0;
    result.b = 0;
    for (int dy = -1; dy<2; ++dy)
        for (int x_coef = 0; x_coef <= 1; ++x_coef)
        {
            int true_y = y+dy;
            int true_x = x+x_direction*x_coef;
            increment(result, divide(start[true_y*width + true_x], 6.f));
        }
    return result;
}
t_my_rgba
cpu_corner
(
        t_my_rgba *start,
        int x,
        int y,
        int x_direction,
        int y_direction,
        int width
)
{
    t_my_rgba result;
    result.a = 0;
    result.r = 0;
    result.g = 0;
    result.b = 0;
    for (int y_coef = 0; y_coef <= 1; ++y_coef)
        for (int x_coef = 0; x_coef <= 1; ++x_coef)
        {
            int true_x = x+x_direction*x_coef;
            int true_y = y+y_direction*y_coef;
            increment(result, divide(start[true_y*width + true_x], 4.f));
        }
    return result;
}

void
cpu_filter
(
        Array2D<Rgba> &pixels,
        int width,
        int height,
        t_times &cpu_time
)
{   
    t_my_rgba *buffer = (t_my_rgba*)malloc(width*height*sizeof(t_my_rgba));
    t_my_rgba *output = (t_my_rgba*)malloc(width*height*sizeof(t_my_rgba));
    
    {
        ScopeClock dummy(&cpu_time.transfer_to);
        copy(buffer, pixels, width, height);
    }
    {
        ScopeClock dummy(&cpu_time.processing);
        for (int x = 1; x < width - 1; ++x)
        {
            for (int y = 1; y < height - 1; ++y)
            {
                output[y*width + x] = cpu_middle_filter(buffer, x, y, width);
            }
        }
        for (int x = 1; x < width - 1; ++x)
        {
            output[0*width + x] = cpu_y_edge_filter(buffer, x, 0, 1, width);
            output[(height-1)*width + x] = cpu_y_edge_filter(buffer, x, height - 1, -1, width);
        }
        for (int y = 1; y < height - 1; ++y)
        {
            output[y*width+0] = cpu_x_edge_filter(buffer, 0, y, 1, width);
            output[y*width + width-1] = cpu_x_edge_filter(buffer, width-1, y, -1, width);
        }
        output[0*width + 0] = cpu_corner(buffer, 0, 0, 1, 1, width);
        output[0*width + width-1] = cpu_corner(buffer, width-1, 0, -1, 1, width);
        output[(height-1)*width+0] = cpu_corner(buffer, 0, height-1, 1, -1, width);
        output[(height-1)*width + width-1] = cpu_corner(buffer, width-1, height-1, -1, -1, width);
    }
    {
        ScopeClock dummy(&cpu_time.transfer_from);
        copy(pixels, output, width, height);
    }
    free(output);
    free(buffer);
}
