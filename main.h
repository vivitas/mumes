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
#include <ImfArray.h>

#include <ImfRgba.h>

using namespace std;
using namespace Imf;

/* files input and output */
const string k_input_directory = "/media/filip/Local/dev/exr/";
const string k_output_directory = "/media/filip/Local/dev/exr_output/";

vector<string> get_all_files_from_directory(string directory);
void empty_directory(string directory);

/* Preuzeto sa OpenEXR primera */

void
 writeRgba1 (const char fileName[],
 const Rgba *pixels,
 int width,
 int height);

void
 readRgba1 (const char fileName[],
 Array2D<Rgba> &pixels,
 int &width,
 int &height);

#endif	/* MAIN_H */

