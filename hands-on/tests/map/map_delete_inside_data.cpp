int main()
{
  int a[100];
  #pragma omp target enter data map(alloc:a)
  #pragma omp target data map(alloc:a)
  {
    #pragma omp target exit data map(delete:a)
  }
}
