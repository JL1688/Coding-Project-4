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
#include <chrono>

// function to add the elements of two arrays
// Input arguments:
// - n: The number of elements in arrays x and y
// - x: The first array of n elements
// - y: The second array of n elements (result vector).
void add(int n, float *x, float *y)
{
  for (int i = 0; i < n; i++)
    y[i] = x[i] + y[i];
}

int main(void)
{
  int N = 1 << 29; // 512M elements

  float *x = new float[N];
  float *y = new float[N];

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++)
  {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // start timer code
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

  // Run kernel on 512M elements on the CPU
  add(N, x, y);

  // end timer code, and print out the elapsed time for this problem size
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;
  std::cout << " Elapsed time is : " << elapsed.count() << " " << std::endl;

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
  {
    maxError = fmax(maxError, fabs(y[i] - 3.0f));
  }

  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  delete[] x;
  delete[] y;

  return 0;
}
