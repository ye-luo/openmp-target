add_library(array_class dualspace.f90)

foreach(NAME device device_isptr resize)
  set(FULLNAME dualspace_array_${NAME})
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
