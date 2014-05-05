/* 
 * File:   file_type_converter.cpp
 * Author: filip
 *
 * Created on May 4, 2014, 3:32 PM
 */

#include <cstdlib>
#include "main.h"
#include "file_system_operations.h"

#include "open_exr_io.h"
#include "my_hdr_io.h"

#include <string.h>

#include "common_filter.h"

using namespace std;

void usage()
{
    cout << "This program converts .exr file to .myhdr file format and vice versa" << endl;
    cout << "Provide argument \"to\" or \"from\" and both conversions will be done by default" << endl;
}
/*
 * 
 */
int main(int argc, char** argv) {
    bool convert_from_exr = true;
    bool convert_to_exr = true;
    if (argc == 1)
    {
        usage();
    }
    else
    {
        if (strcmp(argv[1], "to") == 0)
        {
            convert_from_exr = false;
        }
        else if (strcmp(argv[1], "from") == 0)
        {
            convert_to_exr = false;
        }
        else
        {
            convert_to_exr = convert_from_exr = false;
            usage();
        }
    }
    if (convert_from_exr)
    {
        Array2D<Rgba> pixels(1, 1);
        t_my_rgba *raw_pixels;        
        int width, height;        
        vector<string> all_files = get_all_files_from_directory(k_input_directory_exr);
        empty_directory(k_input_directory_myhdr);
        for (vector<string>::iterator i = all_files.begin(); i == all_files.begin(); ++i) {
                string input_file_name = k_input_directory_exr + *i;
                string output_file_name = k_input_directory_myhdr + *i + ".myhdr";
                cout << endl << "converting: " << *i  << " to my_hdr"<< endl;
                readRgba1(input_file_name.c_str(), pixels, width, height);
                raw_pixels = (t_my_rgba*)malloc(width * height * sizeof(t_my_rgba));
                copy(raw_pixels, pixels, width, height);
                write_my_hdr(output_file_name.c_str(), raw_pixels, width, height);
                free(raw_pixels);
        }
    }
    if (convert_to_exr)
    {
        Array2D<Rgba> pixels(1, 1);
        t_my_rgba *raw_pixels;
        int width, height;
        vector<string> all_files = get_all_files_from_directory(k_output_directory_myhdr);
        empty_directory(k_output_directory_exr);
        for (vector<string>::iterator i = all_files.begin(); i == all_files.begin(); ++i) {
                string input_file_name = k_output_directory_myhdr + *i;
                string output_file_name = k_output_directory_exr + *i + ".exr";
                cout << endl << "converting: " << *i  << " to exr"<< endl;
                read_my_hdr(input_file_name.c_str(), &raw_pixels, width, height);
                //pixels.resizeErase(width, height);
                //copy(pixels, raw_pixels, width, height);
                //writeRgba1(output_file_name.c_str(), pixels, width, height);
                free(raw_pixels);
        }
    }
    return 0;
}

