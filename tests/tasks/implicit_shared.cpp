#include <iostream>

void foo(int& x)
{
  #pragma omp task if(0)
  {
    x++;
    std::cout << "inside " << x << std::endl;
  }
}

int main()
{
  std::cout << "Test task in-place" << std::endl;
  int x = 0;
  #pragma omp parallel
  {
    #pragma omp single
    {
      #pragma omp task if(0)
      {
        x++;
        std::cout << "inside " << x << std::endl;
      }
    }
  }
  std::cout << "outside " << x << std::endl;

  std::cout << "Test task in functon" << std::endl;
  x = 0;
  #pragma omp parallel
  {
    #pragma omp single
    {
      foo(x);
    }
  }
  std::cout << "outside " << x << std::endl;
}
