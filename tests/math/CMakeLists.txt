if (ENABLE_CXX)
  foreach(NAME FP_ZERO header_only modf sqrt_simd sin_cos sin_simd sincos sincos_simd sincos_simd_template modf_in_branch)
    set(FULLNAME ${NAME})
    set(EXE_NAME cxx.math_${FULLNAME})
    add_executable(${EXE_NAME} ${FULLNAME}.cpp)
    set_target_properties(${EXE_NAME} PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME ${EXE_NAME}
             COMMAND $<TARGET_FILE:${EXE_NAME}>
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(${EXE_NAME} PROPERTIES LABELS cxx)
  endforeach()
endif()
