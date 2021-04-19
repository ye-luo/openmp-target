#include <stdexcept>
#include <iostream>

int main()
{
  int a = 0;
  std::cout << "outside a = " << a << " addr " << &a << std::endl;
  #pragma omp target map(tofrom: a) depend(out: a) nowait
  {
    int sum = 0;
    for (int i = 0; i < 100000; i++)
      sum++;
    a = 1;
  }

  #pragma omp task depend(in: a) shared(a)
  {
    std::cout << "a = " << a << " addr " << &a << std::endl;
    if (a != 1)
      throw std::runtime_error("wrong result!");
  }

  #pragma omp taskwait
  return 0;
}
