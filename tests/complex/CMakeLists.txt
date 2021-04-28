if (ENABLE_CXX)
  foreach(NAME complex_reduction_cpu complex_reduction complex)
    set(FULLNAME ${NAME})
    add_executable(cxx.${FULLNAME}.x ${FULLNAME}.cpp)
    set_target_properties(cxx.${FULLNAME}.x PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME cxx.${FULLNAME}
             COMMAND cxx.${FULLNAME}.x
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(cxx.${FULLNAME} PROPERTIES
                         LABELS CXX)
  endforeach()
endif()

if (ENABLE_Fortran)
  set(FULLNAME complex)
  add_executable(f.${FULLNAME}.x ${FULLNAME}.f90)
  set_target_properties(f.${FULLNAME}.x PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME f.${FULLNAME}
           COMMAND f.${FULLNAME}.x
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(f.${FULLNAME} PROPERTIES
                       LABELS fortran)
endif()
