#define N 8192
#include <iostream>

template <typename T>
void gemv(int n, T alpha, const T* restrict A, const T* restrict V, T* restrict Vout)
{
  #pragma omp parallel for
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
  auto* A = allocate<float>(N*N);
  auto* V = allocate<float>(N);
  auto* Vout = allocate<float>(N);

  gemv(N, 1.0f, A, V, Vout);

  deallocate(A, N*N);
  deallocate(V, N);
  deallocate(Vout, N);
}
