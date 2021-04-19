if (ENABLE_CXX)
  foreach(NAME teams_private__distribute _teams_private__distribute teams_distribute_private teams__distribute_private _teams_distribute_private _teams__distribute_private teams_distribute_parallel_for_private)
    set(FULLNAME target_${NAME})
    add_executable(${FULLNAME}.cxx.x ${FULLNAME}.cpp)
    add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
    set_tests_properties(${FULLNAME}.cxx PROPERTIES
                         LABELS CXX)
  endforeach()
endif()

if (ENABLE_Fortran)
  foreach(NAME parallel_for_private private)
    set(FULLNAME target_teams_distribute_${NAME})
    add_executable(${FULLNAME}.f.x ${FULLNAME}.f90)
    add_test(NAME ${FULLNAME}.f COMMAND ${FULLNAME}.f.x)
    set_tests_properties(${FULLNAME}.f PROPERTIES
                         LABELS fortran)
  endforeach()
endif()
