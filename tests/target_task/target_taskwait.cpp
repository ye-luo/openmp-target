#include <stdexcept>
#include <iostream>

int main()
{
  int a = 0;
  std::cout << "outside a = " << a << " addr " << &a << std::endl;
  #pragma omp target nowait
  {
    int sum = 0;
    for (int i = 0; i < 100000; i++)
      sum++;
    a = 1;
  }

  #pragma omp taskwait
  return 0;
}
