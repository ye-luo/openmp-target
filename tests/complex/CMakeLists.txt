if (ENABLE_CXX)
  foreach(NAME complex_reduction_cpu complex_reduction complex)
    set(FULLNAME ${NAME})
    set(EXE_NAME cxx.${FULLNAME})
    add_executable(${EXE_NAME} ${FULLNAME}.cpp)
    set_target_properties(${EXE_NAME} PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME ${EXE_NAME}
             COMMAND $<TARGET_FILE:${EXE_NAME}>
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(${EXE_NAME} PROPERTIES LABELS cxx)
  endforeach()
endif()

if (ENABLE_Fortran)
  set(FULLNAME complex)
  set(EXE_NAME f.${FULLNAME})
  add_executable(${EXE_NAME} ${FULLNAME}.f90)
  set_target_properties(${EXE_NAME} PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME ${EXE_NAME}
           COMMAND $<TARGET_FILE:${EXE_NAME}>
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(${EXE_NAME} PROPERTIES LABELS fortran)
endif()
