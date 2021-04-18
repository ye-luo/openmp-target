#include <iostream>
#include <complex>

bool failed = false;

#if !defined(__NO_UDR)
#pragma omp declare reduction(+: std::complex<float>: omp_out += omp_in)
#pragma omp declare reduction(+: std::complex<double>: omp_out += omp_in)
#endif

template<typename T>
void test_reduction()
{
  T sum(0), sum_host(0);
  const int size = 100;
  T array[size];
  for (int i = 0; i < size; i++)
  {
    array[i] = T(i);
    sum_host += array[i];
  }

  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < size; i++)
    sum += array[i];

  if (std::abs(sum - sum_host) > 1e-6)
  {
    std::cout << "wrong reduction value check" << sum << " correct value " << sum_host << std::endl;
    failed = true;
  }
}

int main()
{
  test_reduction<float>();
  test_reduction<std::complex<float>>();
  test_reduction<double>();
  test_reduction<std::complex<double>>();
  return failed;
}
