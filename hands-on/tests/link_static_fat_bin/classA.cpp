#include "classA.h"

template<typename T>
void tester<T>::run()
{
  #pragma omp target
  {
    T a;
  }
}

template class tester<double>;
