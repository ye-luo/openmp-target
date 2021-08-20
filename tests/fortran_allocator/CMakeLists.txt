add_library(array_class OMPTargetArrayClass.f90)

foreach(NAME device device_ptr device_isptr device_ptr_isptr)
  set(FULLNAME allocatable_array_${NAME})
  set(EXE_NAME f.${FULLNAME})
  add_executable(${EXE_NAME} ${FULLNAME}.f90)
  target_link_libraries(${EXE_NAME} PUBLIC array_class)
  set_target_properties(${EXE_NAME} PROPERTIES
                       RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME ${EXE_NAME}
           COMMAND $<TARGET_FILE:${EXE_NAME}>
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(${EXE_NAME} PROPERTIES LABELS fortran)
endforeach()
