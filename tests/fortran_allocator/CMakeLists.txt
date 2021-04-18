foreach(NAME device device_ptr device_isptr device_ptr_isptr)
  set(FULLNAME allocatable_array_${NAME})
  add_executable(${FULLNAME}.f.x ${FULLNAME}.f90)
  add_test(NAME ${FULLNAME} COMMAND ${FULLNAME}.f.x)
  set_tests_properties(${FULLNAME} PROPERTIES
                       LABELS fortran)
endforeach()
