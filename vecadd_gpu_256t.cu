//
// Code Source: https://developer.nvidia.com/blog/even-easier-introduction-cuda/
//
// Modified by: Jiqing Liu
// course #:656-01, assignment number: 2025_05_09: CP#4 CPU version of vector addition code
// 05/09/2025
// 1-sentence description here: implementation of vector addition code (CPU version)
//

#include <iostream>
#include <math.h>

// function to add the elements of two arrays
// Input arguments:
// - n: The number of elements in arrays x and y
// - x: The first array of n elements
// - y: The second array of n elements (result vector).
__global__ 
void add(int n, float *x, float *y)
{
    int index = threadIdx.x;
    int stride = blockDim.x;
    for (int i = index; i < n; i += stride)
        y[i] = x[i] + y[i];
}

int main(void)
{
    int N = 1 << 29; // 512M elements

    float *x, *y;

    // Allocate Unified Memory – accessible from CPU or GPU
    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));

    // initialize x and y arrays on the host
    for (int i = 0; i < N; i++)
    {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // Run kernel on 512M elements on the GPU
    add<<<1, 256>>>(N, x, y);

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    // Check for errors (all values should be 3.0f)
    float maxError = 0.0f;
    for (int i = 0; i < N; i++)
    {
        maxError = fmax(maxError, fabs(y[i] - 3.0f));
    }

    std::cout << "Max error: " << maxError << std::endl;

    // Free memory
    cudaFree(x);
    cudaFree(y);
    return 0;
}
