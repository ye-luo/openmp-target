set(TEST_OPENMP_RUNTIME_SOURCE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/try_openmp_runtime.f90)
file(WRITE ${TEST_OPENMP_RUNTIME_SOURCE}
"program test_open_runtime
  use omp_lib
  implicit none
  integer :: num
  num = omp_get_thread_num()
end program
")


try_compile(Fortran_OPENMP_RUNTIME_OKAY ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp
            ${TEST_OPENMP_RUNTIME_SOURCE}
            OUTPUT_VARIABLE COMPILE_OUTPUT)

if (NOT Fortran_OPENMP_RUNTIME_OKAY)
  set(COMPILE_FAIL_OUTPUT fortran_openmp_runtime_compile_fail.txt)
  file(WRITE "${CMAKE_BINARY_DIR}/${COMPILE_FAIL_OUTPUT}" "${COMPILE_OUTPUT}")
  message(STATUS "Fortran OpenMP functionality check failed!"
                 "See compiler output at ${COMPILE_FAIL_OUTPUT}")
  add_library(dummy_openmp_runtime cmake/DummyOpenMPRuntime.f90)
  fix_fortran_modules(dummy_openmp_runtime)
else()
  add_library(dummy_openmp_runtime INTERFACE)
  message(STATUS "Fortran OpenMP functionality check pass")
endif()
