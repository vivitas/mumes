#include "file_system_operations.h"

#ifndef MUMES_WINDOWS
#include <dirent.h>
#else
#include <Windows.h>
#endif
#include <stdlib.h>

vector<string>
get_all_files_from_directory
(
        string directory_path
)
{
	vector<string> result;
#ifndef MUMES_WINDOWS
    DIR *directory;
    directory = opendir(directory_path.c_str());
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
#else
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory_path + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return result; /* No files found */

	do {
		const string file_name = file_data.cFileName;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;

		result.push_back(file_name);
	} while (FindNextFile(dir, &file_data));

	FindClose(dir);
#endif
    return result;
}

void
empty_directory
(
        string directory
)
{
#ifdef MUMES_WINDOWS
    system((string("exec rm -r ")+directory+string("*")).c_str());
#else
#endif
}
