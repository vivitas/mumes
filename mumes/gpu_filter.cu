#include "gpu_filter.h"
#include "cuda_runtime.h"
#include <stdio.h>
static void HandleError(cudaError_t err,
                        const char *file,
                        int line)
{
    if(err != cudaSuccess)
    {
        printf("%s in %s at line %d\n", cudaGetErrorString(err),
               file, line);
        getchar();
        getchar();
        exit(EXIT_FAILURE);
    }
}
#define MAX(A, B) (A>B?A:B)
#define MIN(A, B) (A<B?A:B)
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))
__global__ void
gpu_kernel
(
    float *src,
    float *dst,
    int width,
    int height,
    int depth
)
{
    if(blockIdx.x >= width || blockIdx.y >= height || threadIdx.x >= 4)
        return;
    int x_from = MAX(blockIdx.x - 1, 0);
    int y_from = MAX(blockIdx.y - 1, 0);
    int x_to = MIN(blockIdx.x + 1, width - 1);
    int y_to = MIN(blockIdx.y + 1, height - 1);
    int coef = (x_to - x_from + 1) * (y_to - y_from - 1);
    dst[threadIdx.x + 4 * blockIdx.x + 4 * width*blockIdx.y] = 0.f;
 
    float b = 0;
    
    for(int x_ = x_from; x_ <= x_to; ++x_)
    {
        for(int y_ = y_from; y_ <= y_to; ++y_)
        {            
            b += src[threadIdx.x + 4 * x_ + 4 * width*y_] / coef;
        }
    }
    dst[threadIdx.x + 4 * blockIdx.x + 4 * width * blockIdx.y] = b;
}
void
gpu_filter
(
    t_RGBA *raw,
    int width,
    int height,
    int depth
)
{
    float *gpu_src, *gpu_dst;
    HANDLE_ERROR(cudaMalloc(&gpu_src, width*height*depth*sizeof(t_RGBA)));
    HANDLE_ERROR(cudaMalloc(&gpu_dst, width*height*depth*sizeof(t_RGBA)));
    HANDLE_ERROR(cudaMemcpy(gpu_src, raw, width*height*depth*sizeof(t_RGBA), cudaMemcpyHostToDevice));
    dim3 grid(width, height);
    gpu_kernel <<< grid, 4 >> > (gpu_src, gpu_dst, width, height, depth);
    HANDLE_ERROR(cudaGetLastError());
    HANDLE_ERROR(cudaMemcpy(raw, gpu_dst, width*height*depth*sizeof(t_RGBA), cudaMemcpyDeviceToHost));
    cudaFree(gpu_src);
    cudaFree(gpu_dst);
}