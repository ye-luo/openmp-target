#define N 8192
#include <iostream>
#include <chrono>
#include <string>

template <typename T>
void gemv(int n, T alpha, const T* restrict A, const T* restrict V, T* restrict Vout)
{
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

class Timer
{
  const std::chrono::time_point<std::chrono::system_clock> start;
  const std::string name;

public:
  Timer(const std::string& name_in): start(std::chrono::system_clock::now()), name(name_in) {};
  ~Timer()
  {
    auto end = std::chrono::system_clock::now();
    std::cout << "Function " << name
              << " takes " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " us" << std::endl;
  }
};

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
