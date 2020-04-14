#include <iostream>
#include <complex>

template<typename T>
void test_complex()
{
  std::complex<T> a(0, 1), b(0.5, 0.3), c;
  std::complex<T> a_check;
  #pragma omp target map(from:a_check)
  {
    a_check = a;
  }

  if (std::abs(a - a_check) > 1e-6)
  {
    std::cout << "wrong map value check" << a_check << " correct value " << a << std::endl;
  }

  #pragma omp target map(from:c)
  {
    c = a * b;
  }

  if (std::abs(c - a * b) > 1e-6)
    std::cout << "wrong a * b (" << std::real(c) << "," << std::imag(c) << "), "
              << "correct value (" << std::real(a*b) << "," << std::imag(a*b) << ")" << std::endl;
}

template<typename T>
void test_plus()
{
  std::complex<T> a(0, 1), b(0.5, 0.3), c, c_host(a + b);
  #pragma omp target map(from:c)
  {
    c = a + b;
  }

  if (std::abs(c - c_host) > 1e-6)
  {
    std::cout << "wrong operator plus value check" << c << " correct value " << c_host << std::endl;
  }
}

int main()
{
  test_complex<float>();
  test_complex<double>();

  test_plus<float>();
  return 0;
}
