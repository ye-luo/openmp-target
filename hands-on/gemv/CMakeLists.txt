if (ENABLE_CXX)
  set(CXX_SRCS
    01-gemv-omp/gemv-omp.cpp
    02-gemv-omp-target/gemv-omp-target.cpp
    03-gemv-omp-target-teams/gemv-omp-target-teams.cpp
    04-gemv-omp-target-reduction/gemv-omp-target-reduction.cpp
    05-gemv-omp-target-split-parallel-for-reduction/gemv-omp-target-split-parallel-for-reduction.cpp
    51-gemv-omp-many-matrices/gemv-omp-many-matrices.cpp
    52-gemv-omp-target-many-matrices-no-hierachy/gemv-omp-target-many-matrices-no-hierachy.cpp
    53-gemv-omp-target-many-matrices/gemv-omp-target-many-matrices.cpp
    54-gemv-omp-target-many-matrices-multi-devices/gemv-omp-target-many-matrices-multi-devices.cpp
    55-gemv-omp-target-many-matrices-taskloop/gemv-omp-target-many-matrices-taskloop.cpp
  )

  foreach(full_file_name IN ITEMS ${CXX_SRCS})
    get_filename_component(name_only ${full_file_name} NAME_WE)
    set(EXE_NAME cxx.${name_only})
    add_executable(${EXE_NAME} ${full_file_name})
    target_compile_definitions(${EXE_NAME} PUBLIC -DTHROW_FAIL)
    target_include_directories(${EXE_NAME} PUBLIC ../common)
    add_test(NAME ${EXE_NAME}
             COMMAND $<TARGET_FILE:${EXE_NAME}>)
    set_tests_properties(${EXE_NAME} PROPERTIES LABELS cxx)
  endforeach()
endif()
