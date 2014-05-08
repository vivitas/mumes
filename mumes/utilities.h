#pragma once
#include "IL\il.h"
#include "common.h"

void
load_image
(
	ILuint image,
	char* file
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
char *file
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
