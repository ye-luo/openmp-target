cmake_minimum_required(VERSION 3.14)

# set the project name
project(openmp-target LANGUAGES NONE)

OPTION(ENABLE_CXX "Enable/disable C++ tests" ON)
OPTION(ENABLE_Fortran "Enable/disable Fortran tests" ON)
OPTION(ENABLE_EXPERIMENTAL "Enable/disable experimental tests" OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (ENABLE_CXX)
  enable_language(CXX)
  # requires C++14 standard
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
  include(cmake/TestCXXOpenMPRuntime.cmake)
endif()

if (ENABLE_Fortran)
  enable_language(Fortran)
  include(cmake/TestFortranOpenMPRuntime.cmake)
endif()

enable_testing()

if (CMAKE_CXX_COMPILER_ID MATCHES "PGI" OR CMAKE_CXX_COMPILER_ID MATCHES "NVHPC")
  add_definitions(-D__NO_UDR)
endif()

add_subdirectory(hands-on)
add_subdirectory(tests)
