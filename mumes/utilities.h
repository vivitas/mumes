#pragma once
#include "IL\il.h"
#include "common.h"
#include <string>
#include <vector>

using namespace std;

void
load_image
(
	ILuint image,
	const char* file
);

void
copy_image
(
	ILuint dst,
	ILuint src
);

void
save_image
(
	ILuint image,
	const char *file
);

void
get_raw_rgba
(
	ILuint image,
	t_RGBA *&raw,
	int &width,
	int &height,
	int &depth
);

void
set_raw_rgba
(
	ILuint image,
	t_RGBA *raw,
	int width,
	int height,
	int depth
);

vector<string>
get_all_files_from_directory
(
    string directory
);
bool
exists
(
    const std::string& name
);