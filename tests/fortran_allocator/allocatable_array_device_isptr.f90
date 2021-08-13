subroutine sum_on_device(array, array_size)
  implicit none
  integer, intent(in) :: array_size
  real(kind = 8), intent(in) :: array(1:array_size)
  integer :: i, Nsum
 
! do a sum
Nsum = 0
!$omp target teams distribute parallel do reduction(+: Nsum) is_device_ptr(array)
do i = 1, array_size
  Nsum = Nsum + array(i)
enddo

write(*,*) "Nsum = ", Nsum

if (Nsum /= 500500) stop 1
end subroutine

subroutine test
use OMPTargetArrayClass
implicit none
type(OMPTargetArrayDP) :: abc
integer, parameter :: Ntotal = 1000
integer :: i

call abc%resize(Ntotal)

! initialize values
!$omp target teams distribute parallel do map(always, from:abc%array)
do i = 1, Ntotal
  abc%array(i) = i
enddo

!$omp target data use_device_ptr(abc%array)
call sum_on_device(abc%array, size(abc%array))
!$omp end target data

!write(*,*) "end of subroutine"
end subroutine test

program main
call test()
!write(*,*) "end of program"
end program main
