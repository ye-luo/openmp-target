if (ENABLE_CXX)
  foreach(NAME teams_private__distribute _teams_private__distribute teams_distribute_private teams__distribute_private _teams_distribute_private _teams__distribute_private teams_distribute_parallel_for_private)
    set(FULLNAME target_${NAME})
    set(EXE_NAME cxx.${FULLNAME})
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
  foreach(NAME parallel_for_private private)
    set(FULLNAME target_teams_distribute_${NAME})
    set(EXE_NAME f.${FULLNAME})
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
