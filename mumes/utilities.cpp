#include "utilities.h"
void
load_image
(
ILuint image,
char* file
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
char *file
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