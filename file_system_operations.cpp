#include "file_system_operations.h"

#include <dirent.h>
#include <stdlib.h>

vector<string>
get_all_files_from_directory
(
        string directory_path
)
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
empty_directory
(
        string directory
)
{
    system((string("exec rm -r ")+directory+string("*")).c_str());
}
