#include <cassert>

int main()
{
  int in = 1;
  int out = 0;
  int n = 2;
  for(int i = 0; i < n; i++)
  {
    #pragma omp target map(from:out)
    {
      out = in * 2;
    }
  }
  assert( out == in * 2 );
}
