foreach(NAME device device_ptr device_isptr device_ptr_isptr)
  set(FULLNAME allocatable_array_${NAME})
  add_executable(f.${FULLNAME}.x ${FULLNAME}.f90)
  set_target_properties(f.${FULLNAME}.x PROPERTIES
                       RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME f.${FULLNAME}
           COMMAND f.${FULLNAME}.x
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(f.${FULLNAME} PROPERTIES
                       LABELS fortran)
endforeach()
