/* 
 * File:   main.cpp
 * Author: filip
 *
 * Created on May 3, 2014, 10:13 AM
 */

#include <cstdlib>
#include <iostream>
#include <dirent.h>

#include "main.h"

/*
 * Main file with all code
 */

using namespace std;

int main(int argc, char** argv) {
    vector<string> all_files = get_all_files_from_directory(k_input_directory);
    for (vector<string>::iterator i = all_files.begin(); i!= all_files.end(); ++i)
        cout<< *i << endl;
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

