#include <iostream>
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_thread_num() { return 1; }
#endif

int main()
{
  const int size = 4;
  int wrong_counts = 0;
  #pragma omp parallel reduction(+:wrong_counts)
  {
    int A[size];
    for(int i = 0; i < size; i++)
      A[i] = 0;

    #pragma omp target teams distribute map(tofrom: A[:size])
    for(int i = 0; i < size; i++)
    {
      A[i] = i;
    }

    #pragma omp critical
    {
      std::cout << "tid = " << omp_get_thread_num() << std::endl;
      for(int i = 0; i < size; i++)
      {
        if (A[i] != i) wrong_counts++;
        std::cout << "  " << A[i];
      }
      std::cout << std::endl;
    }
  }

  if (wrong_counts)
    std::cout << "Wrong!" << std::endl;
  else
    std::cout << "Right!" << std::endl;
  return wrong_counts;
}
