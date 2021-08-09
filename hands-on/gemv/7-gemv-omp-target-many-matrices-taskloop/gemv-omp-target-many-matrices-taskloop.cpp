#define N 256
#include <vector>
#include <sstream>
#include "timer.h"

template<typename T>
void gemv(int n, T alpha, const T* __restrict__ A, const T* __restrict__ V, T* __restrict__ Vout)
{
#pragma omp target teams distribute map(to : A[:n * n], V[:n]) map(from : Vout[:n]) nowait
  for (int row = 0; row < n; row++)
  {
    T sum                       = T(0);
    const T* __restrict__ A_row = A + row * n;
#pragma omp parallel for reduction(+ : sum)
    for (int col = 0; col < n; col++)
      sum += A_row[col] * V[col];
    Vout[row] = sum * alpha;
  }
}

template<typename T>
void gemv_host(int n, T alpha, const T* __restrict__ A, const T* __restrict__ V, T* __restrict__ Vout)
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
#pragma omp target enter data map(to : ptr[:n])
  return ptr;
}

template<class T>
void deallocate(T* ptr, size_t n)
{
#pragma omp target exit data map(delete : ptr[:n])
  delete[] ptr;
}

int main()
{
  std::vector<float*> manyA;
  std::vector<float*> manyV;
  std::vector<float*> manyVout;

  const int Num_calc = 512;
  for (int i = 0; i < Num_calc; i++)
  {
    manyA.push_back(allocate<float>(N * N));
    manyV.push_back(allocate<float>(N));
    manyVout.push_back(allocate<float>(N));
  }

  // warm up
#pragma omp parallel
  {
#pragma omp target nowait
    { int a = 1; }
  }

  {
    Timer local("multiGEMV parallel taskloop");
#pragma omp parallel
    #pragma omp single
    #pragma omp taskloop
    for (int i = 0; i < Num_calc; i++)
      if (i%2)
        gemv(N, 1.0f, manyA[i], manyV[i], manyVout[i]);
      else
        gemv_host(N/16, 1.0f, manyA[i], manyV[i], manyVout[i]);
  }

  for (int i = 0; i < Num_calc; i++)
  {
    auto* __restrict__ Vout = manyVout[i];
    if (i%2)
    {
#pragma omp target update from(Vout[:N])
    for (int j = 0; j < N; j++)
      if (Vout[j] != N)
      {
        std::cerr << "Calculation " << i << " Vout[" << j << "] != " << N << ", wrong value is " << Vout[j]
                  << std::endl;
        break;
      }
    }

    deallocate(manyA[i], N * N);
    deallocate(manyV[i], N);
    deallocate(manyVout[i], N);
  }
}
