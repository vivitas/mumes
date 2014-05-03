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
#include <ImfRgbaFile.h>
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
    empty_directory(k_output_directory);
    
    for (vector<string>::iterator i = all_files.begin(); i != all_files.end(); ++i) {
        string input_file_name = k_input_directory + *i;
        string output_file_name = k_output_directory + *i;
        cout << endl << "Working on: " << *i << endl;

        Array2D<Rgba> pixels(1, 1);
        int width;
        int height;
        readRgba1(input_file_name.c_str(), pixels, width, height);
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y) {
            }
        writeRgba1(output_file_name.c_str(), &pixels[0][0], width, height);

    }
    return 0;
}

vector<string> get_all_files_from_directory(string directory_path) {
    DIR *directory;

    directory = opendir(directory_path.c_str());
    vector<string> result;
    if (directory) {
        struct dirent *entry = readdir(directory);
        while (entry != NULL) {
            if (entry->d_name[0] != '.') {
                result.push_back(string(entry->d_name));
            }
            entry = readdir(directory);
        }
        closedir(directory);
    }
    return result;
}

void
writeRgba1(const char fileName[],
        const Rgba *pixels,
        int width,
        int height) {
    RgbaOutputFile file(fileName, width, height, WRITE_RGBA); // 1
    file.setFrameBuffer(pixels, 1, width); // 2
    file.writePixels(height); // 3
}

void
readRgba1(const char fileName[],
        Array2D<Rgba> &pixels,
        int &width,
        int &height) {
    RgbaInputFile file(fileName);
    Box2i dw = file.dataWindow();
    width = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    pixels.resizeErase(height, width);
    file.setFrameBuffer(&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file.readPixels(dw.min.y, dw.max.y);
}

void
empty_directory(string directory)
{
    system((string("exec rm -r ")+directory+string("*")).c_str());
}