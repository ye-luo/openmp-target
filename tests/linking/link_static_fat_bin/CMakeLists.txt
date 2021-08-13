if (ENABLE_CXX)
  set(FULLNAME link_static_fat_bin)
  add_library(mylib classA.cpp)
  add_executable(cxx.${FULLNAME}.x main.cpp)
  target_link_libraries(cxx.${FULLNAME}.x mylib)
  set_target_properties(cxx.${FULLNAME}.x PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
  add_test(NAME cxx.${FULLNAME}
           COMMAND cxx.${FULLNAME}.x
           WORKING_DIRECTORY ${TESTS_BINDIR})
  set_tests_properties(cxx.${FULLNAME} PROPERTIES
                       LABELS cxx)
endif()
