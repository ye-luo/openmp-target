//#include <omp.h>
#include <iostream>

template <typename T> struct base {
  T abc[20];
  T de[200];
  T compute() { return de[0]; }
};

template <typename T> struct foo : protected base<T> {
  foo() {
#pragma omp target enter data map(to : this[:1])
  }
  ~foo() {
#pragma omp target exit data map(delete : this[:1])
  }

  void target_compute() {
    //std::cout << "  ***** is this[:1] mapped? " << omp_target_is_present(this, omp_get_default_device()) << std::endl;
#pragma omp target teams
#pragma omp parallel
    { T a = base<T>::compute(); }
  }
};

int main() {
  foo<int> a;
  a.target_compute();
}
