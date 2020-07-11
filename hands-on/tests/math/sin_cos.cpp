#include <cmath>
#include <cassert>

template<typename T>
void test_sin_cos(T x)
{
  T res_sin, res_cos;

  #pragma omp target map(from: res_sin, res_cos)
  {
    res_sin = std::sin(x);
    res_cos = std::cos(x);
  }

  assert(res_sin == std::sin(x));
  assert(res_cos == std::cos(x));
}

int main()
{

#if !defined(C_ONLY)
  test_sin_cos<double>(0.0);
  test_sin_cos<float>(0.0);
#endif

  #pragma omp target
  {
    double res;
    res = sin(1.0);
  }

  #pragma omp target
  {
    float res;
    res = sinf(1.0f);
  }

  return 0;
}
