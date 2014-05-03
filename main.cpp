/* 
 * File:   main.cpp
 * Author: filip
 *
 * Created on May 3, 2014, 10:13 AM
 */


#include "open_exr_io.h"
#include "main.h"
#include "file_system_operations.h"
#include "cpu_filter.h"
#include "gpu_filter.h"

#include <cstdlib>
#include <iostream>

/*
 * Main file with all code
 */

using namespace std;

Array2D<Rgba> pixels(1, 1);
        
int
main
(
        int argc,
        char** argv
)
{
    vector<string> all_files = get_all_files_from_directory(k_input_directory);
    empty_directory(k_output_directory);
    
    for (vector<string>::iterator i = all_files.begin(); i != all_files.end(); ++i) {
        string input_file_name = k_input_directory + *i;
        string output_file_name = k_output_directory + *i;
        cout << endl << "Working on: " << *i << endl;
        int width;
        int height;
        readRgba1(input_file_name.c_str(), pixels, width, height);
        t_times cpu_time, gpu_time;
        cpu_filter(pixels, width, height, cpu_time);
        cout << "CPU:" << endl;
        cout << "transfer to   : " << cpu_time.transfer_to << endl;
        cout << "processing    : " << cpu_time.processing << endl;
        cout << "transfer from : " << cpu_time.transfer_from << endl;
        gpu_filter(pixels, width, height, gpu_time);
        cout << "GPU:" << endl;
        cout << "transfer to   : " << gpu_time.transfer_to << endl;
        cout << "processing    : " << gpu_time.processing << endl;
        cout << "transfer from : " << gpu_time.transfer_from << endl;
        writeRgba1(output_file_name.c_str(), &pixels[0][0], width, height);
    }
    return 0;
}

