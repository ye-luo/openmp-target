if (ENABLE_Fortran)
  foreach(NAME parallel_for_private private)
    set(FULLNAME target_teams_distribute_${NAME})
    add_executable(${FULLNAME}.f.x ${FULLNAME}.f90)
    add_test(NAME ${FULLNAME} COMMAND ${FULLNAME}.f.x)
    set_tests_properties(${FULLNAME} PROPERTIES
                         LABELS fortran)
  endforeach()
endif()
