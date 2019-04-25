#define N 8192
#include "timer.h"

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
  std::fill_n(ptr, n, T(1));
  //#pragma omp target enter data map(to:ptr[:n])
  return ptr;
}

template <class T>
void deallocate(T* ptr, int n)
{
  //#pragma omp target exit data map(delete:ptr[:n])
  delete[] ptr;
}

int main()
{
  auto* A = allocate<float>(N*N);
  auto* V = allocate<float>(N);
  auto* Vout = allocate<float>(N);

  {
    Timer local("GEMV");
    gemv(N, 1.0f, A, V, Vout);
  }

  deallocate(A, N*N);
  deallocate(V, N);
  deallocate(Vout, N);
}
