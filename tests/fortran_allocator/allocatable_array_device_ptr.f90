subroutine test
use OMPTargetArrayClass
implicit none
type(OMPTargetArrayDP), target :: abc
integer, parameter :: Ntotal = 1000
integer :: i, Nsum
real(kind = 8), pointer :: array_ptr(:)

call abc%resize(Ntotal)

array_ptr => abc%array
! initialize values
!$omp target teams distribute parallel do map(always, from:array_ptr)
do i = 1, Ntotal
  array_ptr(i) = i
enddo

! do a sum
Nsum = 0
!$omp target teams distribute parallel do reduction(+: Nsum) map(tofrom: array_ptr)
do i = 1, Ntotal
  Nsum = Nsum + array_ptr(i)
enddo

write(*,*) "Nsum = ", Nsum

if (Nsum /= 500500) stop 1
!write(*,*) "end of subroutine"
end subroutine test

program main
call test()
!write(*,*) "end of program"
end program main
