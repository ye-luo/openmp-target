#include <iostream>
#include <complex>

int main()
{
  std::complex<float> a(0, 1), b(0.5, 0.3), c;
  #pragma omp target map(from:c)
  {
    c = a * b;
  }

  if (std::abs(c - a * b) > 1e-6)
    std::cout << "wrong a * b (" << std::real(c) << "," << std::imag(c) << "), "
              << "correct value (" << std::real(a*b) << "," << std::imag(a*b) << ")" << std::endl;
  return 0;
}
