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

template<typename RT, typename AT, typename BT>
void test_plus(AT a, BT b)
{
  std::complex<RT> c, c_host;

  c_host = a + b;
  #pragma omp target map(from:c)
  {
    c = a + b;
  }

  if (std::abs(c - c_host) > 1e-6)
  {
    std::cout << "wrong operator + value check" << c << " correct value " << c_host << std::endl;
  }
}

template<typename RT, typename AT, typename BT>
void test_minus(AT a, BT b)
{
  std::complex<RT> c, c_host;

  c_host = a - b;
  #pragma omp target map(from:c)
  {
    c = a - b;
  }

  if (std::abs(c - c_host) > 1e-6)
  {
    std::cout << "wrong operator - value check" << c << " correct value " << c_host << std::endl;
  }
}

template<typename RT, typename AT, typename BT>
void test_mul(AT a, BT b)
{
  std::complex<RT> c, c_host;

  c_host = a * b;
  #pragma omp target map(from:c)
  {
    c = a * b;
  }

  if (std::abs(c - c_host) > 1e-6)
  {
    std::cout << "wrong operator * value check" << c << " correct value " << c_host << std::endl;
  }
}

template<typename RT, typename AT, typename BT>
void test_div(AT a, BT b)
{
  std::complex<RT> c, c_host;

  c_host = a / b;
  #pragma omp target map(from:c)
  {
    c = a / b;
  }

  if (std::abs(c - c_host) > 1e-6)
  {
    std::cout << "wrong operator / value check" << c << " correct value " << c_host << std::endl;
  }
}

#pragma omp declare reduction(+: std::complex<float>: omp_out += omp_in)
#pragma omp declare reduction(+: std::complex<double>: omp_out += omp_in)

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
    std::cout << "wrong operator / value check" << sum << " correct value " << sum_host << std::endl;
  }
}

template<typename T>
void test_complex()
{
  test_map<T>();

  test_plus<T>(std::complex<T>(0, 1), std::complex<T>(0.5, 0.3));
  test_plus<T>(std::complex<T>(0, 1), T(0.5));
  test_plus<T>(T(0.5), std::complex<T>(0, 1));

  test_minus<T>(std::complex<T>(0, 1), std::complex<T>(0.5, 0.3));
  test_minus<T>(std::complex<T>(0, 1), T(0.5));
  test_minus<T>(T(0.5), std::complex<T>(0, 1));

  test_mul<T>(std::complex<T>(0, 1), std::complex<T>(0.5, 0.3));
  test_mul<T>(std::complex<T>(0, 1), T(0.5));
  test_mul<T>(T(0.5), std::complex<T>(0, 1));

  test_div<T>(std::complex<T>(0, 1), std::complex<T>(0.5, 0.3));
  test_div<T>(std::complex<T>(0, 1), T(0.5));
  test_div<T>(T(0.5), std::complex<T>(0, 1));

  test_reduction<T>();
}

int main()
{
  test_complex<float>();
  test_complex<double>();
  return 0;
}
