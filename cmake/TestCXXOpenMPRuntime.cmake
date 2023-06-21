include(CheckCXXSourceCompiles)

list(PREPEND OPENMP_CXX_COMPILE_OPTIONS ${OPENMP_CXX_FLAGS} ${OPENMP_FLAGS})
list(PREPEND OPENMP_CXX_LINK_OPTIONS ${OPENMP_CXX_FLAGS} ${OPENMP_FLAGS})

set(CMAKE_REQUIRED_FLAGS ${OPENMP_CXX_COMPILE_OPTIONS})
#set(CMAKE_REQUIRED_LINK_OPTIONS ${OPENMP_CXX_LINK_OPTIONS})

check_cxx_source_compiles(
"#include <omp.h>
int main()
{ int a = omp_get_num_threads(); }"
CXX_OPENMP_RUNTIME_OKAY
)

add_library(qmc_openmp_cxx INTERFACE)

if (CXX_OPENMP_RUNTIME_OKAY)
  message(STATUS "C++ OpenMP functionality check failed!")
else()
  message(STATUS "C++ OpenMP functionality check pass")
  target_compile_options(qmc_openmp_cxx INTERFACE "${OPENMP_CXX_COMPILE_OPTIONS}")
  target_link_options(qmc_openmp_cxx INTERFACE "${OPENMP_CXX_LINK_OPTIONS}")
endif()

check_cxx_source_compiles(
"#include <omp.h>
int main()
{ int a = omp_target_is_present(nullptr, 0); }"
CXX_OFFLOAD_RUNTIME_OKAY
)

if (CXX_OFFLOAD_RUNTIME_OKAY)
  message(STATUS "CXX compiler has OpenMP offload runtime library.")
else()
  message(STATUS "CXX compiler doesn't have OpenMP offload runtime library.")
endif()
