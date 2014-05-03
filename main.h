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
const string k_input_directory = "/media/filip/Local/dev/exr/";
const string k_output_directory = "/media/filip/Local/dev/exr_output/";

struct t_times
{
    int transfer_to;
    int processing;
    int transfer_from;
};

#endif	/* MAIN_H */

