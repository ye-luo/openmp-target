if (ENABLE_CXX)
  foreach(NAME target_nowait_task taskloop_offload_nowait)
    set(FULLNAME ${NAME})
    add_executable(${FULLNAME}.cxx.x ${FULLNAME}.cpp)
    add_test(NAME ${FULLNAME}.cxx COMMAND ${FULLNAME}.cxx.x)
    set_tests_properties(${FULLNAME}.cxx PROPERTIES
                         LABELS CXX)
  endforeach()
endif()
