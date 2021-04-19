if (ENABLE_CXX)
  foreach(NAME FP_ZERO header_only modf sin_cos sincos sincos_simd sincos_simd_template)
    set(FULLNAME ${NAME})
    add_executable(target_math_${FULLNAME}.cxx.x ${FULLNAME}.cpp)
    add_test(NAME target_math_${FULLNAME}.cxx COMMAND target_math_${FULLNAME}.cxx.x)
    set_tests_properties(target_math_${FULLNAME}.cxx PROPERTIES
                         LABELS CXX)
  endforeach()
endif()
