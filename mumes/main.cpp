#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

#include "utilities.h"
#include "cpu_filter.h"
#include "gpu_filter.h"
#include <iostream>

#define __MUMES_CUDA_
#define __MUMES_CPU_
using namespace std;
void
process_file
(
    string file_name,
    string input_directory,
    string output_directory
)
{
    ILuint image = ilGenImage();

#ifdef __MUMES_CUDA_
    ILuint cuda_image = ilGenImage();
    t_RGBA *cuda_raw;
    t_timing cuda_time;
    string cuda_output(output_directory + "cuda_");
#endif

#ifdef __MUMES_CPU_
    ILuint cpu_image = ilGenImage();
    t_RGBA *cpu_raw;
    t_timing cpu_time;
    string cpu_output(output_directory + "cpu_");
#endif

    try
    {
        load_image(image, (input_directory+file_name).c_str());
        if(ilEnable(IL_FILE_OVERWRITE) != IL_TRUE)
            throw "cannot set file mode properly";

        int width, height, depth;

#ifdef __MUMES_CUDA_
        copy_image(cuda_image, image);

        get_raw_rgba(cuda_image, cuda_raw, width, height, depth);
        cuda_time = gpu_filter(cuda_raw, width, height, depth);
        set_raw_rgba(cuda_image, cuda_raw, width, height, depth);

        cout << "gpu: " << endl;
        cout << "\t" << "util:" << cuda_time.utilities_time << endl;
        cout << "\t" << "transfer:" << cuda_time.transfer_time << endl;
        cout << "\t" << "processing:" << cuda_time.processing_time << endl;
        cout << endl;

        save_image(cuda_image, (cuda_output + file_name).c_str());

        delete[] cuda_raw;
#endif

#ifdef __MUMES_CPU_
        copy_image(cpu_image, image);

        get_raw_rgba(cpu_image, cpu_raw, width, height, depth);
        cpu_time = cpu_filter(cpu_raw, width, height, depth);
        set_raw_rgba(cpu_image, cpu_raw, width, height, depth);

        cout << "cpu: " << endl;
        cout << "\t" << "util:" << cpu_time.utilities_time << endl;
        cout << "\t" << "transfer:" << cpu_time.transfer_time << endl;
        cout << "\t" << "processing:" << cpu_time.processing_time << endl;
        cout << endl;

        save_image(cpu_image, (cpu_output + file_name).c_str());

        delete[] cpu_raw;
#endif

        save_image(image, "J:/resources/exr_out/location_1_1_hdr.exr");
    }
    catch(char* c)
    {
        MessageBox(NULL, (LPCSTR) c, (LPCSTR)"error ocured", NULL);
    }
    ilDeleteImage(image);
#ifdef __MUMES_CUDA_
    ilDeleteImage(cuda_image);
#endif
#ifdef __MUMES_CPU_
    ilDeleteImage(cpu_image);
#endif

}
int main()
{

	ilInit();
	iluInit();
	ilutInit();
	
    string input_directory("J:/resources/exr/");
    string original_output("J:/resources/exr_out/");

    vector<string> all_input_files = get_all_files_from_directory(input_directory);
    for(auto i = all_input_files.begin(); i != all_input_files.end(); ++i)
    {
        process_file(*i, input_directory, original_output);
    }	
	MessageBox(NULL, (LPCSTR)"Finished!", (LPCSTR)"Info", NULL);
}