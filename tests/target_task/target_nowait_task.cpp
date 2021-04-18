#include <cassert>

int main()
{
  int a = 0;
  #pragma omp target map(tofrom: a) depend(out: a) nowait
  {
    int sum = 0;
    for (int i = 0; i < 100000; i++)
      sum++;
    a = 1;
  }

  #pragma omp task depend(in: a) shared(a)
  {
    assert(a == 1);
  }

  #pragma omp taskwait
  return 0;
}
