#include <cstdio>
#define LENGTH 2
int main()
{
  constexpr double h_chebyshev_coefs[LENGTH] = { 0, 2.1 };
#pragma omp target enter data map(to:h_chebyshev_coefs[0:LENGTH])
  #pragma omp target
  {
    printf("print in target %lf %lf\n", h_chebyshev_coefs[0], h_chebyshev_coefs[1]);
  }
  return 0;
}
