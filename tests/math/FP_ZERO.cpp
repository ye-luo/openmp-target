//===--- qmcpack_target_math.c --- math lib invocation inside target---------===//
//
// OpenMP API Version 4.5 Nov 2015
//
//
////===----------------------------------------------------------------------===//

#include <iostream>
#include <cstdlib>
#include <cmath>

#define N 1000
bool failed = false;

void test_math_lib_inside_target() {

  double array[N];
  int errors = 0;
  
  // Array initialization
  for (int i = 0; i < N; ++i) {
    array[i] = 0.99;
  }

  int c99_zero = FP_ZERO;

#pragma omp target map(tofrom: array[0:N]) 
  for (int i = 0; i < N; ++i) {
    array[i] = pow((double)i,2.0);
  }

  for (int i = 0; i < N; ++i) {
    if(fabs(array[i] - pow((double)i,2)) >= 0.000009)
    {
      std::cout << "failed array[" << i << "] " << array[i] << " ref " << pow((double)i,2) << std::endl;
      failed = true;
    }
  }
}

int main() {
  test_math_lib_inside_target();
  return failed;
}
