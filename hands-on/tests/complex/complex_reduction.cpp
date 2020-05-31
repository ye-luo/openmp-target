#include <iostream>
#include <complex>

template<typename T>
void test_map()
{
  std::complex<T> a(0.2, 1), a_check;
  #pragma omp target map(from:a_check)
  {
    a_check = a;
  }

  if (std::abs(a - a_check) > 1e-6)
  {
    std::cout << "wrong map value check" << a_check << " correct value " << a << std::endl;
  }
}

#if !defined(__NO_UDR)
#pragma omp declare reduction(+: std::complex<float>: omp_out += omp_in)
#pragma omp declare reduction(+: std::complex<double>: omp_out += omp_in)
#endif

template<typename T>
void test_reduction()
{
  std::complex<T> sum(0), sum_host(0);
  const int size = 100;
  std::complex<T> array[size];
  for (int i = 0; i < size; i++)
  {
    array[i] = {T(i), T(-i)};
    sum_host += array[i];
  }

  #pragma omp target teams distribute parallel for map(to: array[:size]) reduction(+: sum)
  for (int i = 0; i < size; i++)
    sum += array[i];

  if (std::abs(sum - sum_host) > 1e-6)
  {
    std::cout << "wrong reduction value check" << sum << " correct value " << sum_host << std::endl;
  }
}

template<typename T>
void test_complex()
{
  test_map<T>();
  test_reduction<T>();
}

int main()
{
  test_complex<float>();
  test_complex<double>();
  return 0;
}
