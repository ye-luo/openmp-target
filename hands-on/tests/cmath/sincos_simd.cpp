#include <cmath>
#include <cassert>
//#include <iostream>
//#include <iomanip>

constexpr size_t N = 128;

int main()
{
  double phase[N], sinval[N], cosval[N];
  phase[0] = 0.0;
  phase[1] = 0.1;
  phase[2] = 0.2;
  phase[3] = 0.3;

#pragma omp simd
  for(int i = 0; i < N; i++)
  {
    sincos(phase[i], &sinval[i], &cosval[i]);
    //std::cout << std::setprecision(14) << sinval[i] << " " << cosval[i] << std::endl;
  } 

  assert( std::fabs(sinval[0]) < 1e-6);
  assert( std::fabs(sinval[1] - 0.099833416646828) < 1e-6);
  assert( std::fabs(sinval[2] - 0.19866933079506) < 1e-6);
  assert( std::fabs(sinval[3] - 0.29552020666134) < 1e-6);
  assert( std::fabs(cosval[0] - 1) < 1e-6);
  assert( std::fabs(cosval[1] - 0.99500416527803) < 1e-6);
  assert( std::fabs(cosval[2] - 0.98006657784124) < 1e-6);
  assert( std::fabs(cosval[3] - 0.95533648912561) < 1e-6);
}
