#include <cmath>
#include <cstdio>
#include <stdexcept>

template<typename T>
int foo(T r, T DeltaRInv)
{
    r *= DeltaRInv;
    T ipart;
    //printf("modf input %lf ptr %p \n", r, &ipart);
    const T t   = std::modf(r, &ipart);
    const int i = (int)ipart;
    return i;
}

int main()
{
  int arr[20];
  #pragma omp target teams distribute map(arr)
  for(int i = 0; i < 2; i++)
  {
    double r = 1.3;
    double DeltaRInv = 0.3;
    #pragma omp parallel for
    for(int j = 0; j < 10; j++)
    {
      if (r * j > 5)
        arr[i*10 + j] = foo(r * j, DeltaRInv);
      else
        arr[i*10 + j] = 0;
    }
  }

  for(int i = 0; i < 2; i++)
  {
    double r = 1.3;
    double DeltaRInv = 0.3;
    for(int j = 0; j < 10; j++)
      if (r * j > 5)
      {
        if (arr[i*10 + j] != foo(r * j, DeltaRInv)) throw std::runtime_error("Wrong foo return value!");
      }
      else
      {
        if (arr[i*10 + j] != 0) throw std::runtime_error("should be zero!");
      }
  }
}
