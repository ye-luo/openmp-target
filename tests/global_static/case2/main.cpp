#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include "global.h"

void foo(int i)
{
  device_arr[i] *= 2;
}

int main(void)
{
  int host_id   = omp_get_initial_device();
  int device_id = omp_get_default_device();
  
  int N = 5;

  // Allocate and initialize host array
  size_t sz = N * sizeof(int);
  int * host_arr = (int *) malloc(sz);
  for( int i = 0; i < N; i++ )
  {
    host_arr[i] = i;
  }

  // Allocate device array and copy data from host -> device
  device_arr = (int *) omp_target_alloc(sz, device_id);
  omp_target_memcpy(device_arr, host_arr, sz, 0, 0, device_id, host_id);
  #pragma omp target update to(device_arr)

  // Execute device kernel
  #pragma omp target teams distribute parallel for
  for( int i = 0; i < N; i++)
  {
    foo(i);
  }
  
  // Copy data from device -> host
  omp_target_memcpy(host_arr, device_arr, sz, 0, 0, host_id, device_id);

  // Return non-zero error code if we failed
  return host_arr[4] != 8;
}
