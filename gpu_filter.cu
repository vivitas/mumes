#include "gpu_filter.h"
#include "common_filter.h"
#include "ScopeClock.h"

#include <cuda.h>
#include <cuda_runtime.h>

#include <stdio.h>

static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

void
gpu_filter
(
        Array2D<Rgba> &pixels,
        int width,
        int height,
        t_times &time
)
{
    t_my_rgba *input_buffer, *output_buffer;
    alloc_buffers(input_buffer, output_buffer, width, height);
    t_my_rgba *device_input;
    
    HANDLE_ERROR(cudaMalloc((void**)&device_input, sizeof(t_my_rgba)*width*height));
    {
        ScopeClock dummy(&time.transfer_to);
        copy(input_buffer, pixels, width, height);
    }
    {
        ScopeClock dummy(&time.processing);
    }
    {
        ScopeClock dummy(&time.transfer_from);
    }
    cudaFree(device_input);
    free_buffers(input_buffer, output_buffer);
}
