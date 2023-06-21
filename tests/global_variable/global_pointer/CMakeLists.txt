if (ENABLE_CXX AND CXX_OFFLOAD_RUNTIME_OKAY)
  set(FULLNAME global_pointer)
  set(EXE_NAME cxx.${FULLNAME})
  add_executable(${EXE_NAME} main.cpp global.cpp)
  set_target_properties(${EXE_NAME} PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME ${EXE_NAME}
           COMMAND $<TARGET_FILE:${EXE_NAME}>
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(${EXE_NAME} PROPERTIES LABELS cxx)
endif()
