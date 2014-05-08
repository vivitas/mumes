#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

#include "utilities.h"
#include "cpu_filter.h"

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
		copy_image(cpu_image, image);

		int width, height, depth;
		get_raw_rgba(cpu_image, cpu_raw, width, height, depth);
		cpu_filter(cpu_raw, width, height, depth);
		set_raw_rgba(cpu_image, cpu_raw, width, height, depth);
		

		save_image(image, "J:/resources/exr_out/location_1_1_hdr.exr");
		save_image(cuda_image, "J:/resources/exr_out/location_1_1_hdr_cuda.exr");
		save_image(cpu_image, "J:/resources/exr_out/location_1_1_hdr_cpu.exr");

		delete[] cpu_raw;
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