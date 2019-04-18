#define N 2048
#include <iostream>
#include <vector>
#include <omp.h>

template <typename T>
void gemv(int n, T alpha, const T* restrict A, const T* restrict V, T* restrict Vout)
{
  #pragma omp target teams distribute parallel for map(to:A[:n*n], V[:n]) map(from:Vout[:n])
  for(int row=0; row<n; row++)
  {
    T sum = T(0);
    const T *restrict A_row = A+row*n;
    for(int col=0; col<n; col++)
      sum += A_row[col]*V[col];
    Vout[row] = sum*alpha;
  }
}

template <class T>
T* allocate(int n)
{
  T* ptr = new T[n];
  return ptr;
}

template <class T>
void deallocate(T* ptr, int n)
{
  delete[] ptr;
}

int main()
{
  std::vector<float*> manyA;
  std::vector<float*> manyV;
  std::vector<float*> manyVout;

  int Num_calc = 8;
  for(int i=0; i<Num_calc; i++)
  {
    manyA.push_back(allocate<float>(N*N));
    manyV.push_back(allocate<float>(N));
    manyVout.push_back(allocate<float>(N));
  }

  #pragma omp parallel for
  for(int i=0; i<Num_calc; i++)
    gemv(N, 1.0f, manyA[i], manyV[i], manyVout[i]);

  for(int i=0; i<Num_calc; i++)
  {
    deallocate(manyA[i], N*N);
    deallocate(manyV[i], N);
    deallocate(manyVout[i], N);
  }
}
