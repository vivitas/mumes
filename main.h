/* 
 * File:   main.h
 * Author: filip
 *
 * Created on May 3, 2014, 10:12 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <string>
#include <vector>

using namespace std;

/* files input and output */
#ifndef MUMES_WINDOWS
const string k_input_directory_exr = "/media/filip/Local/dev/exr/";
const string k_output_directory_exr = "/media/filip/Local/dev/exr_output/";
const string k_input_directory_myhdr = "/media/filip/Local/dev/my_hdr/";
const string k_output_directory_myhdr = "/media/filip/Local/dev/my_hdr_output/";
#else
const string k_input_directory_exr = "J:\\dev\\exr\\";
const string k_output_directory_exr = "J:\\dev\\exr_output\\";
const string k_input_directory_myhdr = "J:\\dev\\my_hdr\\";
const string k_output_directory_myhdr = "J:\\dev\\my_hdr_output\\";
#endif
struct t_times
{
    int transfer_to;
    int processing;
    int transfer_from;
};

#endif	/* MAIN_H */

