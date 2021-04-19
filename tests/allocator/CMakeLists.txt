if (ENABLE_CXX)
  set(FULLNAME omp_pteam_mem_alloc)
  add_executable(${FULLNAME}.cxx.x ${FULLNAME}.cpp)
  add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
  set_tests_properties(${FULLNAME}.cxx PROPERTIES
                       LABELS CXX)
endif()
