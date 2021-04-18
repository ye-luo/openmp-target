if (ENABLE_CXX)
  set(FULLNAME global_static)
  add_executable(${FULLNAME}.cxx.x main.cpp data.cpp)
  add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
  set_tests_properties(${FULLNAME}.cxx PROPERTIES
                       LABELS CXX)
endif()
