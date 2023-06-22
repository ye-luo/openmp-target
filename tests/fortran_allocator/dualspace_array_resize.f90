subroutine fill_density(density)
  use dualspace, only: dualspace_double_type, dualspace_cplx_double_type
  implicit none
  type(dualspace_double_type), intent(inout) :: density
  real(8), dimension(:), pointer :: density_data
  integer, parameter :: test_size =20
  integer :: i

  call density%resize(test_size)
  density_data => density%data()
  write(*,*) "density_data size ", size(density_data)
  do i = 1, test_size
    density_data(i) = 1.
  enddo
  !$omp target update to(density_data)
  !$omp target teams distribute parallel do map(always, from: density_data)
  do i = 1, test_size
    density_data(i) = density_data(i) + i * 1.
  enddo

  if (density_data(3).ne.4.) stop 1
end subroutine

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
