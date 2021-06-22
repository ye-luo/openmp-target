#define N 8192
#include "timer.h"

// Base code from 1-gemv-omp.cpp

template<typename T> // Creates a template type T to allow passing a data type as a parameter
void gemv(int n, T alpha, const T* __restrict__ A, const T* __restrict__ V, T* __restrict__ Vout)
{
//#pragma omp parallel for // No parallel for vanilla code
  for (int row = 0; row < n; row++)
  { // Multiplies input matrix A with vector V and returns resulting matrix in Vout
    T sum                       = T(0); // Initialize sum
    const T* __restrict__ A_row = A + row * n;
    for (int col = 0; col < n; col++) // 
      sum += A_row[col] * V[col];
    Vout[row] = sum * alpha;
  }
}

template<class T>
T* allocate(size_t n)
{ // Creates matrix
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
  auto* A    = allocate<float>(N * N);
  auto* V    = allocate<float>(N);
  auto* Vout = allocate<float>(N);

  {
    Timer local("GEMV");
    gemv(N, 1.0f, A, V, Vout);
  }

  for (int i = 0; i < N; i++)
    if (Vout[i] != N)
    {
      std::cerr << "Vout[" << i << "] != " << N << ", wrong value is " << Vout[i] << std::endl;
      break;
    }

  deallocate(A, N * N);
  deallocate(V, N);
  deallocate(Vout, N);
}
