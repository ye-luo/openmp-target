if (ENABLE_CXX)
  set(FULLNAME link_static_fat_bin)
  add_executable(${FULLNAME}.cxx.x main.cpp classA.cpp)
  add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
  set_tests_properties(${FULLNAME}.cxx PROPERTIES
                       LABELS CXX)
endif()
