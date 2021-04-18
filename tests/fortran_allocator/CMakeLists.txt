foreach(NAME device device_ptr device_isptr device_ptr_isptr)
  set(FULLNAME allocatable_array_${NAME})
  add_executable(${FULLNAME}.x ${FULLNAME}.f90)
  add_test(NAME ${FULLNAME} COMMAND ${FULLNAME}.x
           PROPERTIES LABELS fortran)
endforeach()
