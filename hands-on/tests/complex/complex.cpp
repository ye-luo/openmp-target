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
    printf("wrong a * b (%f,%f), correct value (%f,%f)\n", std::real(c), std::imag(c), std::real(a*b), std::imag(a*b) );
  return 0;
}
