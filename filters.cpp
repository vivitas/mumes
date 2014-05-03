#include "filters.h"
struct t_my_rgba
{
    float r;
    float g;
    float b;
    float a;
};
t_my_rgba&
to_my_rgba
(
        t_my_rgba& dest,
        Rgba& src
)
{
    dest.a = src.a.operator  float();
    dest.r = src.r.operator  float();
    dest.g = src.g.operator  float();
    dest.b = src.b.operator  float();
    return dest;
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
            to_my_rgba(dest[y*width + x], src[y][x]);            
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
        for (int y = 0; y < height; ++y);
            //dest[y*width + x] = src[y*width + x];
}
void
cpu_filter
(
        Array2D<Rgba> &pixels,
        int width,
        int height,
        t_times &time
)
{   
    t_my_rgba buffer[width][height];
    t_my_rgba output[width][height];
    
    copy(&buffer[0][0], pixels, width, height);
    
    for (int x = 1; x < width - 1; ++x)
    {
        for (int y = 1; y < height - 1; ++y)
        {
            output[y][x] = cpu_middle_filter(&buffer[0][0], x, y, width);
        }
    }
    for (int x = 1; x < width - 1; ++x)
    {
        output[0][x] = cpu_y_edge_filter(&buffer[0][0], x, 0, 1, width);
        output[height-1][x] = cpu_y_edge_filter(&buffer[0][0], x, height - 1, -1, width);
    }
    for (int y = 1; y < height - 1; ++y)
    {
        output[y][0] = cpu_x_edge_filter(&buffer[0][0], 0, y, 1, width);
        output[y][width-1] = cpu_x_edge_filter(&buffer[0][0], width-1, y, -1, width);
    }
    output[0][0] = cpu_corner(&buffer[0][0], 0, 0, 1, 1, width);
    output[0][width-1] = cpu_corner(&buffer[0][0], width-1, 0, -1, 1, width);
    output[height-1][0] = cpu_corner(&buffer[0][0], 0, height-1, 1, -1, width);
    output[height-1][width-1] = cpu_corner(&buffer[0][0], width-1, height-1, -1, -1, width);
    
    copy(pixels, &output[0][0], width, height);           
}
