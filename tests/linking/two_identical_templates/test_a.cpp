#include <iostream>
#include <complex>

template<typename T>
void test_map()
{
  std::cout << "map(complex<>)" << std::endl;
  std::complex<T> a(0.2, 1), a_check;
#pragma omp target map(from : a_check)
  {
    a_check = a;
  }
}

void test_a()
{
  test_map<float>();
}
