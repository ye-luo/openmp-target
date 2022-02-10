#include <iostream>
#include <vector>
#include <string>

struct with_const
{
  with_const()
  {
    #pragma omp target enter data map(to:this[:1])
  }

  constexpr static int size = 6;
  static const int b = 12;
  std::string name;
};

int main()
{
  with_const foo;
  return 0;
}
