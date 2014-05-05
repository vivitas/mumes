#include "my_hdr_io.h"

#include <stdio.h>
#include <stdlib.h>

using namespace std;

void write_my_hdr
(
        const char* output_file_name,
        t_my_rgba *pixels,
        int width,
        int height
)
{
    FILE* output_file = fopen(output_file_name, "wb");
    fprintf(output_file, "%d %d ", width, height);
    cout << width << " " << height << endl;
    t_my_rgba *current_pixel;
    for (int x = 0; x<width; ++x)
        for (int y=0; y<height; ++y)
        {
            current_pixel = pixels + y*width + x;
            fprintf(output_file, "%f %f %f %f ", current_pixel->a, current_pixel->r, current_pixel->g, current_pixel->b);
        }
    fclose(output_file);
}
void
read_my_hdr
(
        const char* input_file_name,
        t_my_rgba **raw_pixels,
        int &width,
        int &height
)
{
    
    FILE* input_file = fopen(input_file_name, "rb");
    
    fscanf(input_file, "%d %d ", &width, &height);    
    cout << width << " " << height << endl;
    *raw_pixels = (t_my_rgba*)malloc(width * height * sizeof(t_my_rgba));
    t_my_rgba *tmp_raw = *raw_pixels;
    for (int x = 0; x<width; ++x)
        for (int y=0; y<height; ++y)
        {
            fscanf(input_file, "%f %f %f %f ", &(tmp_raw[y*width + x].a), &(tmp_raw[y*width + x].r), &(tmp_raw[y*width + x].g), &(tmp_raw[y*width + x].b));
        }
    cout << input_file_name << endl;
    fclose(input_file);
}