#include <vector>
#include <cstdio>

int main()
{
  const int N = 200000000;
  std::vector<float> vec(N, 1.1);
  float* vec_ptr = vec.data();
  for (int it = 0; it < 3; it++)
  {
    printf("\niteration %d\n", it);
    #pragma omp parallel for
    for (int i = 0; i < 4; i++)
    {
      // first hit does the transfer, others start executing the kernel.
      #pragma omp target map(to:vec_ptr[:vec.size()])
      {
        printf("tid %d value = %f\n", i, vec_ptr[N - 1 - i]);
      }
    }
  }
}
