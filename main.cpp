/* 
 * File:   main.cpp
 * Author: filip
 *
 * Created on May 3, 2014, 10:13 AM
 */

#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <ImfInputFile.h>
#include <ImfHeader.h>
#include <ImfBoxAttribute.h>

#include <ImfOutputFile.h>
#include <ImfChannelList.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include "main.h"

/*
 * Main file with all code
 */

using namespace std;
using namespace Imf;
using namespace std;
using namespace Imath;

Array2D<half> rPixels;

int main(int argc, char** argv) {
    vector<string> all_files = get_all_files_from_directory(k_input_directory);
    for (vector<string>::iterator i = all_files.begin(); i!= all_files.end(); ++i)
    {
        string input_file_name = k_input_directory + *i;
        string output_file_name = k_output_directory + *i;
        cout<< endl << "Working on: " << *i << endl;
        
        Array2D<half> rp(1,1);
        int width;
        int height; 
        readGZ1(input_file_name.c_str(), rp, width, height);
        writeGZ1(output_file_name.c_str(), &rp[0][0], width, height);
        
    }
    return 0;
}

vector<string> get_all_files_from_directory(string directory_path)
{
    DIR *directory;
    
    directory = opendir(directory_path.c_str());
    vector<string> result;
    if (directory)
    {
        struct dirent *entry = readdir(directory);
        while (entry != NULL)
        {
            if (entry->d_name[0] != '.')
            {
                result.push_back(string(entry->d_name));
            }
            entry = readdir(directory);
        }
        closedir(directory);
    }
    return result;
}

void
readGZ1 (const char fileName[],
	 Array2D<half> &rPixels,
	 int &width, int &height)
{
    //
    // Read an image using class InputFile.  Try to read two
    // channels, R and G, of type HALF, and one channel, Z,
    // of type FLOAT.  Store the R, G, and Z pixels in three
    // separate memory buffers.
    // If a channel is missing in the file, the buffer for that
    // channel will be filled with an appropriate default value.
    //
    //	- open the file
    //	- allocate memory for the pixels
    //	- describe the layout of the R, G, and Z pixel buffers
    //	- read the pixels from the file
    //

    InputFile file (fileName);

    Box2i dw = file.header().dataWindow();
    width  = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;

    rPixels.resizeErase (height, width);

    FrameBuffer frameBuffer;

    frameBuffer.insert ("R",					// name
			Slice (HALF,			// type
			       (char *) (&rPixels[0][0] -	// base
					 dw.min.x -
					 dw.min.y * width),
			       sizeof (rPixels[0][0]) * 1,	// xStride
			       sizeof (rPixels[0][0]) * width,	// yStride
			       1, 1,				// x/y sampling
			       0.0));				// fillValue

    file.setFrameBuffer (frameBuffer);
    file.readPixels (dw.min.y, dw.max.y);
}

void
writeGZ1 (const char fileName[],
	  const half *gPixels,
	  int width,
	  int height)
{
    //
    // Write an image with only a G (green) and a Z (depth) channel,
    // using class OutputFile.
    //
    //	- create a file header
    //	- add G and Z channels to the header
    //	- open the file, and store the header in the file
    //	- describe the memory layout of the G anx Z pixels
    //	- store the pixels in the file
    //

    Header header (width, height);
    header.channels().insert ("R", Channel (HALF));

    OutputFile file (fileName, header);

    FrameBuffer frameBuffer;

    frameBuffer.insert ("R",					// name
		        Slice (HALF,                    	// type
			       (char *) gPixels,		// base
			       sizeof (*gPixels) * 1,		// xStride
			       sizeof (*gPixels) * width));	// yStride
    file.setFrameBuffer (frameBuffer);
    file.writePixels (height);
}