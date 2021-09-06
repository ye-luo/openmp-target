#include <cassert>
#include <iostream>

class Base
{
public:
  virtual void foo() const = 0;
};

class Derived: public Base
{
  const int const_value = 8;

public:
  Derived()
  {
    #pragma omp target enter data map(to: this[:1])
  }

  ~Derived()
  {
    #pragma omp target exit data map(delete: this[:1])
  }

  void foo() const override {}

  int boo()
  {
    int res = 0;
    #pragma omp target map(from:res)
    {
      res = const_value;
    }
    return res;
  }
};

int main()
{
  Derived a;
  const int res = a.boo();
  std::cout << "return value " << res << " reference value " << 8 << std::endl;
  assert(res == 8);
  return 0;
}
