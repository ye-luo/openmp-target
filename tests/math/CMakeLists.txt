if (ENABLE_CXX)
  foreach(NAME FP_ZERO header_only modf sin_cos sincos sincos_simd sincos_simd_template)
    set(FULLNAME ${NAME})
    add_executable(math_cxx.${FULLNAME}.x ${FULLNAME}.cpp)
    set_target_properties(math_cxx.${FULLNAME}.x PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME cxx.math_${FULLNAME}
             COMMAND math_cxx.${FULLNAME}.x
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(cxx.math_${FULLNAME} PROPERTIES
                         LABELS CXX)
  endforeach()
endif()
