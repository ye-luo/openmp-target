if (ENABLE_CXX)
  foreach(NAME FP_ZERO header_only modf sin_cos sin_simd sincos sincos_simd sincos_simd_template)
    set(FULLNAME ${NAME})
    add_executable(cxx.math_${FULLNAME}.x ${FULLNAME}.cpp)
    set_target_properties(cxx.math_${FULLNAME}.x PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME cxx.math_${FULLNAME}
             COMMAND cxx.math_${FULLNAME}.x
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(cxx.math_${FULLNAME} PROPERTIES
                         LABELS cxx)
  endforeach()
endif()
