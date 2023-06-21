program abc
  use dualspace, only: dualspace_double_type, dualspace_cplx_double_type
  implicit none

  type(dualspace_double_type) :: density, density2
  real(8), dimension(:), pointer :: density_data
  call density%resize(10)
  density_data => density%data()
  write(*,*) "density_data size ", size(density_data)

  call fill_density(density2)
  density_data => density2%data()
  write(*,*) "density_data(3) should be 3. Current value ", density_data(3)

  block
    type(dualspace_cplx_double_type) :: wf
    complex(8), dimension(:), pointer :: wf_data
    call wf%resize(30)
    wf_data =>  wf%data()
    write(*,*) "wf_data size ", size(wf_data)
  end block
end program
