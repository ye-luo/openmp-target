if (ENABLE_CXX)
  foreach(NAME FP_ZERO header_only modf sin_cos sincos sincos_simd sincos_simd_template)
    set(FULLNAME ${NAME})
    add_executable(math_${FULLNAME}.cxx.x ${FULLNAME}.cpp)
    add_test(NAME math_${FULLNAME}.cxx COMMAND math_${FULLNAME}.cxx.x)
    set_tests_properties(math_${FULLNAME}.cxx PROPERTIES
                         LABELS CXX)
  endforeach()
endif()
