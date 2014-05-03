/* 
 * File:   file_system_operations.h
 * Author: filip
 *
 * Created on May 3, 2014, 2:10 PM
 */

#ifndef FILE_SYSTEM_OPERATIONS_H
#define	FILE_SYSTEM_OPERATIONS_H

#include <vector>
#include <string>

using namespace std;

vector<string>
get_all_files_from_directory
(
        string directory_path
);

void
empty_directory
(
        string directory
);

#endif	/* FILE_SYSTEM_OPERATIONS_H */

