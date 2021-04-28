if (ENABLE_CXX)
  foreach(NAME )
    set(FULLNAME pointer_api)
    add_executable(cxx.map_${FULLNAME}.x ${FULLNAME}.cpp)
    set_target_properties(cxx.map_${FULLNAME}.x PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME cxx.map_${FULLNAME}
             COMMAND cxx.map_${FULLNAME}.x
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(cxx.map_${FULLNAME} PROPERTIES
                         LABELS cxx)
  endforeach()
endif()

if (ENABLE_Fortran)
  foreach(NAME implicit_map_alloc)
    set(FULLNAME ${NAME})
    add_executable(f.map_${FULLNAME}.x ${FULLNAME}.f90)
    target_link_libraries(f.map_${FULLNAME}.x dummy_openmp_runtime)
    set_target_properties(f.map_${FULLNAME}.x PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME f.map_${FULLNAME}
             COMMAND f.map_${FULLNAME}.x
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(f.map_${FULLNAME} PROPERTIES
                         LABELS fortran)
  endforeach()
endif()
