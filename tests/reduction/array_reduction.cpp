#include <array>
#include <iostream>

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

void test_size(size_t N)
{
  std::cout << std::endl << "Testing size " << N << std::endl;
  GradType grads{0, 0, 0};
  #pragma omp parallel for reduction(+: grads)
  for (int i = 0; i<N; i++)
    grads[i%3] += i*1.0;
  GradType grads_saved(grads);

  #pragma omp target map(tofrom: grads)
  {
    #pragma omp parallel for reduction(+: grads)
    for (int i = 0; i<N; i++)
      grads[i%3] += i*1.0;
  }
  std::cout << "grads should be twice of grads_saved" << std::endl;
  std::cout << "grads_saved " << grads_saved[0] << " " << grads_saved[1] << " " << grads_saved[2] << std::endl;
  std::cout << "grads       " << grads[0] << " " << grads[1] << " " << grads[2] << std::endl;
  if (std::abs(grads_saved[0] * 2 - grads[0]) > 1e-6 || std::abs(grads_saved[1] * 2 - grads[1]) > 1e-6 || std::abs(grads_saved[2] * 2 - grads[2]) > 1e-6)
  {
    std::cout << "Failed!" << std::endl;
    exit(1);
  }
  else
    std::cout << "Passed!" << std::endl;
}

int main()
{
  std::cout << "Start testing!" << std::endl;
  test_size(9);
  test_size(3);
  test_size(5);
  test_size(7);
  test_size(13);
  test_size(15);
  test_size(17);
  test_size(25);
  test_size(31);
  test_size(35);
  test_size(65);
  test_size(8);
  test_size(16);
  test_size(32);
  test_size(64);
  test_size(128);
  test_size(256);
  std::cout << "End testing!" << std::endl;
}
