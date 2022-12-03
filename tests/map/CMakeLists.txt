if (ENABLE_CXX)
  foreach(NAME pointer_api this_with_virtual struct_with_const first_private_this_wrong)
    set(FULLNAME ${NAME})
    set(EXE_NAME cxx.map_${FULLNAME})
    add_executable(${EXE_NAME} ${FULLNAME}.cpp)
    set_target_properties(${EXE_NAME} PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME ${EXE_NAME}
             COMMAND $<TARGET_FILE:${EXE_NAME}>
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(${EXE_NAME} PROPERTIES LABELS cxx)
  endforeach()
endif()

if (ENABLE_Fortran)
  foreach(NAME implicit_map_alloc)
    set(FULLNAME ${NAME})
    set(EXE_NAME f.map_${FULLNAME})
    add_executable(${EXE_NAME} ${FULLNAME}.f90)
    target_link_libraries(${EXE_NAME} dummy_openmp_runtime)
    set_target_properties(${EXE_NAME} PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${TESTS_BINDIR})
    add_test(NAME ${EXE_NAME}
             COMMAND $<TARGET_FILE:${EXE_NAME}>
             WORKING_DIRECTORY ${TESTS_BINDIR})
    set_tests_properties(${EXE_NAME} PROPERTIES LABELS fortran)
  endforeach()
endif()
