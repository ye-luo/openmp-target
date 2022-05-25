#include <array>
#include <iostream>

#define N 120

struct GradType
{
  float X[3]{0, 0, 0};
  float operator[](size_t i) const { return X[i]; }
  float& operator[](size_t i) { return X[i]; }
};

GradType& operator+=(GradType& a, const GradType& b)
{
  for (int i = 0; i < 3; i++)
    a[i]+=b[i];
  return a;
}

#if !defined(__NO_UDR)
#pragma omp declare reduction(+ : GradType : omp_out += omp_in)
#endif

int main()
{
  GradType grads{0, 0, 0};
  #pragma omp parallel for reduction(+: grads)
  for (int i = 0; i<N; i++)
    grads[i%3] += i*1.0;
  std::cout << grads[0] << " " << grads[1] << " " << grads[2] << std::endl;

  #pragma omp target map(tofrom: grads)
  {
    #pragma omp parallel for reduction(+: grads)
    for (int i = 0; i<N; i++)
      grads[i%3] += i*1.0;
  }
  std::cout << grads[0] << " " << grads[1] << " " << grads[2] << std::endl;
}
