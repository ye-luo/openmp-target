if (ENABLE_CXX)
  set(FULLNAME link_static_fat_bin)
  add_library(mylib classA.cpp)
  add_executable(${FULLNAME}.cxx.x main.cpp)
  target_link_libraries(${FULLNAME}.cxx.x mylib)
  add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
  set_tests_properties(${FULLNAME}.cxx PROPERTIES
                       LABELS CXX)
endif()
