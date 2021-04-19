if (ENABLE_CXX)
  foreach(NAME complex_reduction_cpu complex_reduction complex)
    set(FULLNAME ${NAME})
    add_executable(${FULLNAME}.cxx.x ${FULLNAME}.cpp)
    add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
    set_tests_properties(${FULLNAME}.cxx PROPERTIES
                         LABELS CXX)
  endforeach()
endif()

if (ENABLE_Fortran)
  set(FULLNAME complex)
  add_executable(${FULLNAME}.f.x ${FULLNAME}.f90)
  add_test(NAME ${FULLNAME}.f COMMAND ${FULLNAME}.f.x)
  set_tests_properties(${FULLNAME}.f PROPERTIES
                       LABELS fortran)
endif()
