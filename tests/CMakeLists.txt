add_subdirectory(complex)
add_subdirectory(private)
add_subdirectory(link_static_fat_bin)
add_subdirectory(linker_outlined_func)

if (ENABLE_Fortran)
  add_subdirectory(fortran_use_device_ptr)
  add_subdirectory(fortran_allocator)
endif()
