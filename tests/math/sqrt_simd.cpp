#include <cmath>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <iomanip>

constexpr size_t N = 128;

template<typename T>
void test_sqrt_simd()
{
  T phase[N], sqrtval[N];
  phase[0] = 0.0;
  phase[1] = 0.1;
  phase[2] = 0.2;
  phase[3] = 0.3;

#pragma omp simd
  for(int i = 0; i < N; i++)
  {
    sqrtval[i] = std::sqrt(phase[i]);
    //std::cout << std::setprecision(14) << sqrtval[i] << std::endl;
  } 

  std::cout << std::setprecision(14);
  std::cout << "sqrtval[0] " << sqrtval[0] << " ref " << 0 << std::endl;
  std::cout << "sqrtval[1] " << sqrtval[1] << " ref " << 0.31622776601684 << std::endl;
  std::cout << "sqrtval[2] " << sqrtval[2] << " ref " << 0.44721359549996 << std::endl;
  std::cout << "sqrtval[3] " << sqrtval[3] << " ref " << 0.54772255750517 << std::endl;
  assert( std::fabs(sqrtval[0]) < 1e-6);
  assert( std::fabs(sqrtval[1] - 0.31622776601684) < 1e-6);
  assert( std::fabs(sqrtval[2] - 0.44721359549996) < 1e-6);
  assert( std::fabs(sqrtval[3] - 0.54772255750517) < 1e-6);
}

int main()
{
  test_sqrt_simd<float>();
  test_sqrt_simd<double>();
}
