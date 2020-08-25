#include <cstdio>
#include <cstdlib>
#include <omp.h>

#pragma omp declare target
int * arr;

void foo(int i)
{
  printf("device address %d %p\n", i, arr);
}
#pragma omp end declare target

int main(void)
{
  // Allocate array and set to zero
  int len = 3;
  arr = (int *) calloc( len, sizeof(int) );

  printf("arr omp_target_is_present %d\n", omp_target_is_present(arr, 0));
  #pragma omp target data use_device_ptr(arr)
  {
    printf("arr initial device address %p\n", arr);
  }

  #pragma omp target data map(tofrom: arr[:len])
  {
    printf("arr host address %p\n", arr);
    printf("arr omp_target_is_present %d\n", omp_target_is_present(arr, 0));
    #pragma omp target data use_device_ptr(arr)
    {
      printf("arr device address inside map %p\n", arr);
    }

    #pragma omp target teams distribute parallel for
    for( int i = 0; i < len; i++)
      foo(i);
  }

  printf("arr omp_target_is_present %d\n", omp_target_is_present(arr, 0));
  #pragma omp target data use_device_ptr(arr)
  {
    printf("arr final device address %p\n", arr);
  }

  return 0;
}
