if (ENABLE_Fortran)
  set(FULLNAME complex)
  add_executable(${FULLNAME}.f.x ${FULLNAME}.f90)
  add_test(NAME ${FULLNAME} COMMAND ${FULLNAME}.f.x)
  set_tests_properties(${FULLNAME} PROPERTIES
                       LABELS fortran)
endif()
