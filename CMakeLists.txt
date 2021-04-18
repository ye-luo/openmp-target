cmake_minimum_required(VERSION 3.14)

# set the project name
project(openmp-target)

OPTION(ENABLE_CXX "Enable/disable C++ tests" ON)
OPTION(ENABLE_Fortran "Enable/disable Fortran tests" ON)

if (ENABLE_CXX)
  enable_language(CXX)
endif()

if (ENABLE_Fortran)
  enable_language(Fortran)
endif()

enable_testing()

add_subdirectory(tests)
