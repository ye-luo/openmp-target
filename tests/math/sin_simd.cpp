#include <cmath>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <iomanip>

constexpr size_t N = 128;

int main()
{
  double phase[N], sinval[N];
  phase[0] = 0.0;
  phase[1] = 0.1;
  phase[2] = 0.2;
  phase[3] = 0.3;

#pragma omp simd
  for(int i = 0; i < N; i++)
  {
    sinval[i] = std::sin(phase[i]);
    //std::cout << std::setprecision(14) << sinval[i] << std::endl;
  } 

  std::cout << std::setprecision(14);
  std::cout << "sinval[0] " << sinval[0] << " ref " << 0 << std::endl;
  std::cout << "sinval[1] " << sinval[1] << " ref " << 0.099833416646828 << std::endl;
  std::cout << "sinval[2] " << sinval[2] << " ref " << 0.19866933079506 << std::endl;
  std::cout << "sinval[3] " << sinval[3] << " ref " << 0.29552020666134 << std::endl;
  assert( std::fabs(sinval[0]) < 1e-6);
  assert( std::fabs(sinval[1] - 0.099833416646828) < 1e-6);
  assert( std::fabs(sinval[2] - 0.19866933079506) < 1e-6);
  assert( std::fabs(sinval[3] - 0.29552020666134) < 1e-6);
}
