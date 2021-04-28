set(TEST_OPENMP_RUNTIME_SOURCE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/try_openmp_runtime.f90)
file(WRITE ${TEST_OPENMP_RUNTIME_SOURCE}
"program test_open_runtime
  implicit none
  integer :: num
  integer, external :: omp_get_thread_num
  num = omp_get_thread_num()
end program
")


try_compile(OPENMP_RUNTIME_OKAY ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp
            ${TEST_OPENMP_RUNTIME_SOURCE}
            OUTPUT_VARIABLE COMPILE_OUTPUT)

if (NOT OPENMP_RUNTIME_OKAY)
  set(COMPILE_FAIL_OUTPUT openmp_runtime_compile_fail.txt)
  file(WRITE "${CMAKE_BINARY_DIR}/${COMPILE_FAIL_OUTPUT}" "${COMPILE_OUTPUT}")
  message(STATUS "OpenMP functionality check failed!"
                 "See compiler output at ${COMPILE_FAIL_OUTPUT}")
  add_library(dummy_openmp_runtime cmake/DummyOpenMPRuntime.f90)
else()
  add_library(dummy_openmp_runtime)
  message(STATUS "OpenMP functionality check pass")
endif()
