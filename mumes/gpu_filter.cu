#include "gpu_filter.h"
#include "cuda_runtime.h"
#include <stdio.h>
#include "ScopeTimer.h"

#define TPB 64

static char error[1024];
static void HandleError(cudaError_t err,
                        const char *file,
                        int line)
{
    if(err != cudaSuccess)
    {        
        sprintf(error, "%s in %s at line %d\n", cudaGetErrorString(err),
               file, line);
        throw error;
    }
}
#define MAX(A, B) (A>B?A:B)
#define MIN(A, B) (A<B?A:B)
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))
__global__ void
gpu_kernel
(
    t_RGBA *src,
    t_RGBA *dst,
    int width,
    int height,
    int depth
)
{
    int real_x = blockIdx.x;
    int real_y = blockIdx.y * TPB + threadIdx.x;
    if(real_x >= width || real_y >= height)
        return;
    int x_from = MAX(real_x - 1, 0);
    int y_from = MAX(real_y - 1, 0);
    int x_to = MIN(real_x + 1, width - 1);
    int y_to = MIN(real_y + 1, height - 1);
    int coef = (x_to - x_from + 1) * (y_to - y_from - 1);
 
    dst[real_x + width * real_y].r = 0.f;
    dst[real_x + width * real_y].g = 0.f;
    dst[real_x + width * real_y].b = 0.f;
    dst[real_x + width * real_y].a = 0.f;
        
    for(int x_ = x_from; x_ <= x_to; ++x_)
    {
        for(int y_ = y_from; y_ <= y_to; ++y_)
        {            
            dst[real_x + width * real_y].r += src[x_ + width*y_].r / coef;
            dst[real_x + width * real_y].g += src[x_ + width*y_].g / coef;
            dst[real_x + width * real_y].b += src[x_ + width*y_].b / coef;
            dst[real_x + width * real_y].a += src[x_ + width*y_].a / coef;
        }
    }
    //dst[blockIdx.x + width * blockIdx.y] = b;
}
t_timing
gpu_filter
(
    t_RGBA *&raw,
    int width,
    int height,
    int depth,
    int repetitions
)
{
    t_timing result;
    t_RGBA *gpu_src, *gpu_dst;
    {
        ScopeTimer _dummy(&(result.utilities_time));
        HANDLE_ERROR(cudaMalloc(&gpu_src, width*height*depth*sizeof(t_RGBA)));
        HANDLE_ERROR(cudaMalloc(&gpu_dst, width*height*depth*sizeof(t_RGBA)));
    }
    try
    {
        {
            ScopeTimer _dummy(&(result.transfer_time));
            HANDLE_ERROR(cudaMemcpy(gpu_src, raw, width*height*depth*sizeof(t_RGBA), cudaMemcpyHostToDevice));
        }
        {
            
            dim3 grid(width, height/TPB);
            for(int i = 0; i < repetitions; ++i)
            {
                {
                    ScopeTimer _dummy(&(result.processing_time));
                    gpu_kernel << < grid, TPB >> > (gpu_src, gpu_dst, width, height, depth);
                    HANDLE_ERROR(cudaGetLastError());
                
                    t_RGBA *tmp;
                    tmp = gpu_src;
                    gpu_src = gpu_dst;
                    gpu_dst = tmp;
                }
            }        
        }
        {
            ScopeTimer _dummy(&(result.transfer_time));
            HANDLE_ERROR(cudaMemcpy(raw, gpu_src, width*height*depth*sizeof(t_RGBA), cudaMemcpyDeviceToHost));
        }
        {
            ScopeTimer _dummy(&(result.utilities_time));
            HANDLE_ERROR(cudaFree(gpu_src));
            HANDLE_ERROR(cudaFree(gpu_dst));
        }
    }
    catch(char* c)
    {
        ScopeTimer _dummy(&(result.utilities_time));
        try
        {
            HANDLE_ERROR(cudaFree(gpu_src));
        }
        catch(...)
        {
        }
        try
        {
            HANDLE_ERROR(cudaFree(gpu_dst));
        }
        catch(...)
        {
        }
        throw c;
    }
    return result;
}
void
prepare_cuda_device
(
)
{
    for(int i=0; i<10; ++i)
    {
        void* testMemory;
        HANDLE_ERROR(cudaMalloc(&testMemory, 1024 * 768 * 4 * 4));
        HANDLE_ERROR(cudaFree(testMemory));
    }
}