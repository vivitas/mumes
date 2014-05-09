#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

#include "utilities.h"
#include "cpu_filter.h"
#include "gpu_filter.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define __MUMES_CUDA_
#define __MUMES_CPU_
using namespace std;
void
process_file
(
    string file_name,
    string input_directory,
    string output_directory,
    ofstream &stats
)
{
    ILuint image = ilGenImage();

#ifdef __MUMES_CUDA_
    ILuint cuda_image = ilGenImage();
    t_RGBA *cuda_raw = NULL;
    t_timing cuda_time;
    string cuda_output(output_directory + "cuda_");
#endif

#ifdef __MUMES_CPU_
    ILuint cpu_image = ilGenImage();
    t_RGBA *cpu_raw = NULL;
    t_timing cpu_time;
    string cpu_output(output_directory + "cpu_");
#endif

    try
    {
        load_image(image, (input_directory+file_name).c_str());
        if(ilEnable(IL_FILE_OVERWRITE) != IL_TRUE)
            throw "cannot set file mode properly";

        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);
        int depth = ilGetInteger(IL_IMAGE_DEPTH);

        stats << file_name << "\t" << width << "\t" << height << "\t" << depth;
        stats.flush();

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
        cuda_raw = 0;

        stats << "\t" << cuda_time.transfer_time << "\t" << cuda_time.utilities_time << "\t" << cuda_time.processing_time;
        stats.flush();
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
        cpu_raw = 0;

        stats << "\t" << cpu_time.transfer_time << "\t" << cpu_time.utilities_time << "\t" << cpu_time.processing_time;
        stats.flush();
#endif

        save_image(image, (output_directory+file_name).c_str());
    }
    catch(char* c)
    {
       cout<< endl << c << endl;
    }
    ilDeleteImage(image);
#ifdef __MUMES_CUDA_
    if(cuda_raw != NULL)
    {
        delete[] cuda_raw;
    }
    ilDeleteImage(cuda_image);
#endif
#ifdef __MUMES_CPU_
    if(cpu_raw != NULL)
    {
        delete[] cpu_raw;
    }
    ilDeleteImage(cpu_image);
#endif
    stats << endl;
    stats.flush();
}

int main()
{
	ilInit();
	iluInit();
	ilutInit();
	
    string input_directory("J:/resources/exr/");
    string original_output("J:/resources/exr_out/");
    ostringstream stats_file_path_geneator;
    stats_file_path_geneator << "J:/resources/" << "_stats.csv";
    string stats_file_path(stats_file_path_geneator.str());

    ofstream stats_file;
    if(exists(stats_file_path))
    {
        stats_file.open(stats_file_path, ios_base::app);
    }
    else
    {
        stats_file.open(stats_file_path, ios_base::app);
        stats_file << "image\t" << "width\t" << "height\t" << "depth";
#ifdef __MUMES_CUDA_
        stats_file << "\tcuda transfer\t" << "cuda util\t" << "cuda process";
#endif
#ifdef __MUMES_CPU_
        stats_file << "\tcpu transfer\t" << "cpu util\t" << "cpu process";
#endif
        stats_file << endl;
        stats_file.flush();
    }
#ifdef __MUMES_CUDA_
    prepare_cuda_device();
#endif
    vector<string> all_input_files = get_all_files_from_directory(input_directory);
    for(auto i = all_input_files.begin(); i != all_input_files.end(); ++i)
    {
        process_file(*i, input_directory, original_output, stats_file);
    }
    stats_file.close();
	//MessageBox(NULL, (LPCSTR)"Finished!", (LPCSTR)"Info", NULL);
}