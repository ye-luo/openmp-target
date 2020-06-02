#include <iostream>

template<typename T>
struct maptest
{
  constexpr static int size = 6;
  T data[size];

  maptest()
  {
    std::cout << "before enter data\n";
    #pragma omp target enter data map(alloc:data[:6])
    std::cout << "done with enter data\n";
  }

  ~maptest()
  {
    std::cout << "before exit data\n";
    #pragma omp target exit data map(delete:data[:6])
    std::cout << "done with exit data\n";
  }
};

int main()
{
  maptest<float> a;
}
