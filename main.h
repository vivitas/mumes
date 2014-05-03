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

using namespace std;
using namespace Imf;

const string k_input_directory = "/media/filip/Local/dev/exr/";
const string k_output_directory = "/media/filip/Local/dev/exr_output/";
vector<string> get_all_files_from_directory(string directory);

/* examples */
void
readGZ1 (const char fileName[],
	 Array2D<half> &rPixels,
	 int &width, int &height);

void
writeGZ1 (const char fileName[],
	  const half *gPixels,
	  int width,
	  int height);

#endif	/* MAIN_H */

