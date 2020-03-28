//===--- qmcpack_target_math.c --- math lib invocation inside target---------===//
//
// OpenMP API Version 4.5 Nov 2015
//
//
////===----------------------------------------------------------------------===//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000

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
    assert(fabs(array[i] - pow((double)i,2)) < 0.000009);
  }
}

int main() {
  test_math_lib_inside_target();
}
