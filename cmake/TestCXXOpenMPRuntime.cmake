set(TEST_OPENMP_RUNTIME_SOURCE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/try_openmp_runtime.cpp)
file(WRITE ${TEST_OPENMP_RUNTIME_SOURCE}
"#include <omp.h>
int main()
{
  int a = omp_get_num_threads();
}
")


try_compile(CXX_OPENMP_RUNTIME_OKAY ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp
            ${TEST_OPENMP_RUNTIME_SOURCE}
            OUTPUT_VARIABLE COMPILE_OUTPUT)

if (NOT CXX_OPENMP_RUNTIME_OKAY)
  set(COMPILE_FAIL_OUTPUT cxx_openmp_runtime_compile_fail.txt)
  file(WRITE "${CMAKE_BINARY_DIR}/${COMPILE_FAIL_OUTPUT}" "${COMPILE_OUTPUT}")
  message(STATUS "C++ OpenMP functionality check failed!"
                 "See compiler output at ${COMPILE_FAIL_OUTPUT}")
else()
  message(STATUS "C++ OpenMP functionality check pass")
endif()
