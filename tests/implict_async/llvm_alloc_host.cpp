#include <omp.h>
#include <iostream>

#ifndef __clang_major__
#error Need clang extension
#endif

// expose header free extensions
extern "C" {
void *llvm_omp_target_alloc_host(size_t, int);
void llvm_omp_target_free_host(void *, int);
}

int main() {
  const int N = 64;
  const auto default_device = omp_get_default_device();
  #pragma omp target device(default_device)
  { int a = N; }

  int* hst_ptr = (int*) llvm_omp_target_alloc_host(N * sizeof(int), default_device);

  for (int i = 0; i < N; ++i)
    hst_ptr[i] = 2;

  #pragma omp target teams distribute parallel for device(default_device) map(tofrom : hst_ptr[: N])
  for (int i = 0; i < N; ++i)
    hst_ptr[i] -= 1;

  int sum = 0;
  for (int i = 0; i < N; ++i)
    sum += hst_ptr[i];

  llvm_omp_target_free_host(hst_ptr, default_device);

  if (sum == N)
    std::cout << "Correct Sum" << std::endl;
  else
    std::cout << "Wrong Sum " << sum << "! It should be " << N << std::endl;

  return 0;
}

