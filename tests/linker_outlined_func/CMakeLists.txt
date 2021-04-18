if (ENABLE_CXX)
  set(FULLNAME linker_outlined_function_collision)
  add_executable(${FULLNAME}.cxx.x main.cpp a.cpp b.cpp)
  add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
  set_tests_properties(${FULLNAME}.cxx PROPERTIES
                       LABELS CXX)
endif()
