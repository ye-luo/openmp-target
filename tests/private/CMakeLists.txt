if (ENABLE_CXX)
  foreach(NAME teams_private__distribute _teams_private__distribute teams_distribute_private teams__distribute_private _teams_distribute_private _teams__distribute_private teams_distribute_parallel_for_private)
    set(FULLNAME target_${NAME})
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
  foreach(NAME parallel_for_private private)
    set(FULLNAME target_teams_distribute_${NAME})
    add_executable(f.${FULLNAME}.x ${FULLNAME}.f90)
    set_target_properties(f.${FULLNAME}.x PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME f.${FULLNAME}
             COMMAND f.${FULLNAME}.x
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(f.${FULLNAME} PROPERTIES
                         LABELS fortran)
  endforeach()
endif()
