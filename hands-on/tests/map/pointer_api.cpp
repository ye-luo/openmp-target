#include <iostream>
#include <omp.h>

int main()
{
  int a[1000];
  std::cout << "before enter data mapped? " << omp_target_is_present(a, omp_get_default_device()) << std::endl;
  #pragma omp target enter data map(alloc:a[:1000])
  std::cout << "after enter data mapped? " << omp_target_is_present(a, omp_get_default_device()) << std::endl;
  std::cout << "&a[0] mapped? " << omp_target_is_present(&a[0], omp_get_default_device()) << std::endl;
  std::cout << "&a[50] mapped? " << omp_target_is_present(&a[50], omp_get_default_device()) << std::endl;
  std::cout << "&a[999] mapped? " << omp_target_is_present(&a[999], omp_get_default_device()) << std::endl;
  std::cout << "&a[1000] mapped? " << omp_target_is_present(&a[1000], omp_get_default_device()) << std::endl;

  int* a_ptr = a;
  int* b_ptr = a + 200;

  std::cout << "host pointer " << std::endl
            << "a = " << a_ptr << std::endl
            << "b = " << b_ptr << std::endl;

  #pragma omp target data use_device_ptr(a_ptr, b_ptr)
  {
    std::cout << "device pointer " << std::endl
              << "a = " << a_ptr << std::endl
              << "b = " << b_ptr << std::endl;
  }
}
