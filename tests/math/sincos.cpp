#include <cmath>
#include <iostream>

bool failed = false;

// single precision wrapper
inline void sincos(float x, float* __restrict__ sin, float* __restrict__ cos)
{
  sincosf(x, sin, cos);
}

template<typename T>
void test_sincos(T x)
{
  T res_sin, res_cos;

  #pragma omp target map(from: res_sin, res_cos)
  {
    sincos(x, &res_sin, &res_cos);
  }

  if (res_sin != std::sin(x))
  {
    std::cout << "sincos sin part " << res_sin << " std::sin " << std::sin(x) << std::endl;
    failed = true;
  }
  if (res_cos != std::cos(x))
  {
    std::cout << "sincos cos part " << res_cos << " std::cos " << std::cos(x) << std::endl;
    failed = true;
  }
}

int main(int argc, char **argv)
{

#if !defined(C_ONLY)
  test_sincos<double>(0.0);
  test_sincos<float>(0.0);
#endif

  #pragma omp target
  {
    double s, c;
    sincos(0, &s, &c);
  }

  #pragma omp target 
  {
    float s, c;
    sincosf(0.f, &s, &c);
  }

  return 0;
}
