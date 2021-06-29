#define N 1024
#include "timer.h"

template <typename T>
void gemmT(int n, const T* restrict A, const T* restrict B, T* restrict C)
{
  #pragma omp target teams distribute parallel for collapse(2) map(to:A[:n*n], B[:n*n])  map(tofrom:C[:n*n])
  for(int rowA=0; rowA<n; rowA++)
    for(int rowB=0; rowB<n; rowB++)
    {
      T sum = T(0);
      const T *restrict A_row = A+rowA*n;
      const T *restrict B_row = B+rowB*n;
      for(int colA=0; colA<n; colA++)
        sum += A_row[colA]*B_row[colA];
      C[rowA*n+rowB] = sum;
    }
}

template <class T>
T* allocate(int n)
{
  T* ptr = new T[n];
  std::fill_n(ptr, n, T(1));
  #pragma omp target enter data map(to:ptr[:n])
  return ptr;
}

template <class T>
void deallocate(T* ptr, int n)
{
  #pragma omp target exit data map(delete:ptr[:n])
  delete[] ptr;
}

int main()
{
  auto* A = allocate<float>(N*N);
  auto* B = allocate<float>(N*N);
  auto* C = allocate<float>(N*N);

  {
    Timer local("GEMMT");
    gemmT(N, A, B, C);
  }

  deallocate(A, N*N);
  deallocate(B, N*N);
  deallocate(C, N*N);
}
