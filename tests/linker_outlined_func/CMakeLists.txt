if (ENABLE_CXX)
  set(FULLNAME linker_outlined_function_collision)
  add_executable(cxx.${FULLNAME}.x main.cpp a.cpp b.cpp)
  set_target_properties(cxx.${FULLNAME}.x PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME cxx.${FULLNAME}
           COMMAND cxx.${FULLNAME}.x
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(cxx.${FULLNAME} PROPERTIES
                       LABELS CXX)
endif()
