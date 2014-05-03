#include "filters.h"

Rgba
cpu_middle_filter
(
        Rgba* start,
        int x,
        int y        
);

Rgba
cpu_y_edge_filter
(
        Rgba* start,
        int x,
        int y        
);

Array2D<Rgba>
cpu_filter
(
        Array2D<Rgba> &pixels, 
        int width,
        int height,
        t_times &time
)
{
    Array2D<Rgba> buffer(width, height);
    
    for (int x = 1; x < width - 1; ++x)
    {
        for (int y = 1; y < height - 1; ++y)
        {
            buffer[y][x] = cpu_middle_filter(&pixels[0][0], x, y);
        }
    }
    for (int x = 1; x < width - 1; ++x)
    {
        buffer[0][x] = cpu_y_edge_filter(&pixels[0][0], x, 0);
        buffer[height-1][x] = cpu_y_edge_filter(&pixels[0][0], x, height - 1);
    }
    for 
}
