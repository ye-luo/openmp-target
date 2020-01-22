#include "ab.h"
#include "compute.h"
void b()
{
  const int N = 1000;
  #pragma omp target
  {
    float A[N];
    compute(A, N);
  }
}
