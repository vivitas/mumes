#include "cpu_filter.h"
#include "common.h"
#include <algorithm>

#include "ScopeTimer.h"

using namespace std;

t_RGBA
cpu_avg_from_to
(
	t_RGBA *data,
	int x_from,
	int x_to,
	int y_from,
	int y_to,
	int z,
	int width,
	int height,
	int depth
)
{
	t_RGBA result;
	int number = (x_to - x_from + 1) * (y_to - y_from + 1);
	for (int x = x_from; x <= x_to; ++x)
	{
		for (int y = y_from; y <= y_to; ++y)
		{
			increment(result, data[CORDS(x, y, z)], number);
		}
	}
	return result;
}
t_timing
cpu_filter
(
	t_RGBA *&raw,
	int width,
	int height,
	int depth,
    int repetitions
)
{
    t_timing times;
    t_RGBA *buffer;
    {
        ScopeTimer _dummy(&(times.utilities_time));
        buffer = new t_RGBA[width*height*depth];
    }
    {
        ScopeTimer _dummy(&(times.processing_time));
        for(int i = 0; i < repetitions; i++)
        {
            for(int z = 0; z < depth; ++z)
            {
                for(int y = 0; y < height; ++y)
                {
                    for(int x = 0; x < width; ++x)
                    {
                        int y_from = std::max(y - 1, 0);
                        int x_from = std::max(x - 1, 0);
                        int y_to = std::min(y + 1, height - 1);
                        int x_to = std::min(x + 1, width - 1);
                        buffer[CORDS(x, y, z)] = cpu_avg_from_to(raw, x_from, x_to, y_from, y_to, z, width, height, depth);
                    }
                }
            }
            t_RGBA *tmp = raw;
            raw = buffer;
            buffer = tmp;
        }
    }
    {
        ScopeTimer _dummy(&(times.utilities_time));
        delete[] buffer;
    }
    return times;
}