#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"
#include <iostream>
using namespace std;
struct t_RGBA
{
	float r;
	float g;
	float b;
	float a;
};
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

int main()
{

	ilInit();
	iluInit();
	ilutInit();
	ILuint image, cuda_image, cpu_image;

	t_RGBA *cuda_raw, *cpu_raw;

	image = ilGenImage();
	cuda_image = ilGenImage();
	cpu_image = ilGenImage(); 
	try
	{
		load_image(image, "J:/resources/exr/location_1_1_hdr.exr");
		if (ilEnable(IL_FILE_OVERWRITE) != IL_TRUE)
			throw "cannot set file mode properly";
		copy_image(cuda_image, image);
		cout << endl << endl;
		copy_image(cpu_image, image);

		int width, height, depth;
		get_raw_rgba(cpu_image, cpu_raw, width, height, depth);
		
		set_raw_rgba(cpu_image, cpu_raw, width, height, depth);
		

		save_image(image, "J:/resources/exr_out/location_1_1_hdr.exr");
		save_image(cuda_image, "J:/resources/exr_out/location_1_1_hdr_cuda.exr");
		save_image(cpu_image, "J:/resources/exr_out/location_1_1_hdr_cpu.exr");

		delete[] cpu_raw;
		delete[] cuda_raw;
	}
	catch (char* c)
	{
		MessageBox(NULL, (LPCSTR)c, (LPCSTR)"error ocured", NULL);
	}
	ilDeleteImage(image);
	ilDeleteImage(cuda_image);
	ilDeleteImage(cpu_image);
	MessageBox(NULL, (LPCSTR)"Finished!", (LPCSTR)"Info", NULL);
}