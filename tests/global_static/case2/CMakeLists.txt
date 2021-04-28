if (ENABLE_CXX AND CXX_OPENMP_RUNTIME_OKAY)
  set(FULLNAME global_pointer)
  add_executable(cxx.${FULLNAME}.x main.cpp global.cpp)
  set_target_properties(cxx.${FULLNAME}.x PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME cxx.${FULLNAME}
           COMMAND cxx.${FULLNAME}.x
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(cxx.${FULLNAME} PROPERTIES
                       LABELS cxx)
endif()
