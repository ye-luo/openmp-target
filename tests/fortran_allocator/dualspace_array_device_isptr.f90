subroutine sum_on_device(array, array_size)
  implicit none
  integer, intent(in) :: array_size
  real(kind = 8), intent(in) :: array(1:array_size)
  integer :: i, Nsum
 
! do a sum
Nsum = 0
!$omp target teams distribute parallel do reduction(+: Nsum) has_device_addr(array)
do i = 1, array_size
  Nsum = Nsum + array(i)
enddo

write(*,*) "Nsum = ", Nsum

if (Nsum /= 500500) stop 1
end subroutine

subroutine test
use dualspace
implicit none
type(dualspace_double_type) :: abc
real(8), dimension(:), pointer :: abc_data
integer, parameter :: Ntotal = 1000
integer :: i

call abc%resize(Ntotal)
abc_data => abc%data()

! initialize values
!$omp target teams distribute parallel do map(always, from:abc_data)
do i = 1, Ntotal
  abc_data(i) = i
enddo

!$omp target data use_device_addr(abc_data)
call sum_on_device(abc_data, size(abc_data))
!$omp end target data

!write(*,*) "end of subroutine"
end subroutine test

program main
call test()
!write(*,*) "end of program"
end program main
