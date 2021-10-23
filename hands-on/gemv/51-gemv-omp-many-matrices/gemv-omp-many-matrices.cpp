#define N 4096
#include <vector>
#include "timer.h"

template<typename T>
void gemv(int n, T alpha, const T* __restrict__ A, const T* __restrict__ V, T* __restrict__ Vout)
{
  for (int row = 0; row < n; row++)
  {
    T sum                       = T(0);
    const T* __restrict__ A_row = A + row * n;
    for (int col = 0; col < n; col++)
      sum += A_row[col] * V[col];
    Vout[row] = sum * alpha;
  }
}

template<class T>
T* allocate(size_t n)
{
  T* ptr = new T[n];
  std::fill_n(ptr, n, T(1));
  return ptr;
}

template<class T>
void deallocate(T* ptr, size_t n)
{
  delete[] ptr;
}

int main()
{
  std::vector<float*> manyA;
  std::vector<float*> manyV;
  std::vector<float*> manyVout;

  const int Num_calc = 8;
  for (int i = 0; i < Num_calc; i++)
  {
    manyA.push_back(allocate<float>(N * N));
    manyV.push_back(allocate<float>(N));
    manyVout.push_back(allocate<float>(N));
  }

  {
    Timer local("multiGEMV");
#pragma omp parallel for
    for (int i = 0; i < Num_calc; i++)
      gemv(N, 1.0f, manyA[i], manyV[i], manyVout[i]);
  }

  for (int i = 0; i < Num_calc; i++)
  {
    for (int j = 0; j < N; j++)
      if (manyVout[i][j] != N)
      {
        std::cerr << "Calculation " << i << " Vout[" << j << "] != " << N << ", wrong value is " << manyVout[i][j]
                  << std::endl;
#if defined(THROW_FAIL)
        throw;
#else
        break;
#endif
      }

    deallocate(manyA[i], N * N);
    deallocate(manyV[i], N);
    deallocate(manyVout[i], N);
  }
}
