#include "utilities.h"
#include <Windows.h>
void
load_image
(
	ILuint image,
	const char* file
)
{
	ilBindImage(image);
	if (ilLoad(IL_EXR, file) != IL_TRUE)
		throw "Image loading failed";
}
void
copy_image
(
	ILuint dst,
	ILuint src
)
{
	ilBindImage(dst);
	if (ilCopyImage(src) != IL_TRUE)
		throw "Image copying failed";
}
void
save_image
(
	ILuint image,
	const char *file
)
{
	ilBindImage(image);
	if (ilSave(IL_EXR, file) != IL_TRUE)
		throw "Image saving failed";
}

void
get_raw_rgba
(
	ILuint image,
	t_RGBA *&raw,
	int &width,
	int &height,
	int &depth
)
{
	ilBindImage(image);
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	depth = ilGetInteger(IL_IMAGE_DEPTH);
	int channels = ilGetInteger(IL_IMAGE_CHANNELS);
	if (channels != 4)
		throw "currently only 4-channel pictures are supported";
	raw = new t_RGBA[width*height*depth];
	ilCopyPixels(0, 0, 0, width, height, depth, IL_RGBA, IL_FLOAT, raw);
	return;
}
void
set_raw_rgba
(
	ILuint image,
	t_RGBA *raw,
	int width,
	int height,
	int depth
)
{
	ilBindImage(image);
	int channels = ilGetInteger(IL_IMAGE_CHANNELS);
	if (channels != 4)
		throw "currently only 4-channel pictures are supported";
	ilSetPixels(0, 0, 0, width, height, depth, IL_RGBA, IL_FLOAT, raw);
	return;
}

vector<string>
get_all_files_from_directory
(
    string directory
)
{
    vector<string> result;
    HANDLE entry;
    WIN32_FIND_DATA file_data;

    if((entry = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return result;

    do
    {
        const string file_name = file_data.cFileName;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if(file_name[0] == '.')
            continue;

        if(is_directory)
            continue;

        result.push_back(file_name);
    }
    while(FindNextFile(entry, &file_data));

    FindClose(entry);

    return result;
}
bool
exists
(
    const std::string& name
)
{
    if(FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}
