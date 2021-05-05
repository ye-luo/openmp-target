#include <cassert>
#include "data.hpp"

template<typename T>
void check()
{
  T params_check[4];
  engine<T> mine;

  #pragma omp target map(from:params_check[:4])
  {
    for(int i=0; i<4; i++)
      params_check[i] = mine.params[i];
  }
  assert(params_check[0] == T(1.0));
  assert(params_check[1] == T(2.0));
  assert(params_check[2] == T(3.0));
  assert(params_check[3] == T(4.0));
}

int main()
{
  check<float>();
  check<double>();
}
