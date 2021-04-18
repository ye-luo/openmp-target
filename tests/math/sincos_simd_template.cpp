#include <cmath>
#include <complex>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <iomanip>

constexpr size_t N = 128;

inline void sincos(float phi, float* s, float* c)
{
  sincosf(phi, s, c);
}

template<typename T>
void test_sincos()
{
  T phase[N];
  std::complex<T> scval[N];
  for(int i = 0; i < N; i++)
    phase[i] = 0.1 * i;

  T sum_r(0), sum_i(0);
  for(int i = 0; i < N; i++)
  {
    T s, c;
    sincos(phase[i], &s, &c);
    scval[i] = {s, c};
    sum_r += s;
    sum_i += c;
  } 

  std::cout << std::setprecision(14) << "--------------------------" << std::endl;
  std::cout << "sinval[0] " << scval[0].real() << " ref " << 0 << std::endl;
  std::cout << "sinval[1] " << scval[1].real() << " ref " << 0.099833416646828 << std::endl;
  std::cout << "sinval[2] " << scval[2].real() << " ref " << 0.19866933079506 << std::endl;
  std::cout << "sinval[3] " << scval[3].real() << " ref " << 0.29552020666134 << std::endl;
  std::cout << "cosval[0] " << scval[0].imag() << " ref " << 1 << std::endl;
  std::cout << "cosval[1] " << scval[1].imag() << " ref " << 0.99500416527803 << std::endl;
  std::cout << "cosval[2] " << scval[2].imag() << " ref " << 0.98006657784124 << std::endl;
  std::cout << "cosval[3] " << scval[3].imag() << " ref " << 0.95533648912561 << std::endl;
  assert( std::fabs(scval[0].real()) < 1e-6);
  assert( std::fabs(scval[1].real() - 0.099833416646828) < 1e-6);
  assert( std::fabs(scval[2].real() - 0.19866933079506) < 1e-6);
  assert( std::fabs(scval[3].real() - 0.29552020666134) < 1e-6);
  assert( std::fabs(scval[0].imag() - 1) < 1e-6);
  assert( std::fabs(scval[1].imag() - 0.99500416527803) < 1e-6);
  assert( std::fabs(scval[2].imag() - 0.98006657784124) < 1e-6);
  assert( std::fabs(scval[3].imag() - 0.95533648912561) < 1e-6);

  std::cout << "sum_r " << sum_r << " sum_i " << sum_i << std::endl;
  assert( std::fabs(sum_r - 0.1556929974475) < 1e-4);
  assert( std::fabs(sum_i - 2.3267523980062) < 1e-4);
}

int main()
{
  test_sincos<float>();
  test_sincos<double>();
}
