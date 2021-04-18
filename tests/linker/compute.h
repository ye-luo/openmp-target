inline void compute(float* a, int size)
{
  #pragma omp parallel for
  for (int i = 0; i < size; i++)
    a[i] *= 2.0f;
}
