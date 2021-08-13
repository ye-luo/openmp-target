subroutine test
use OMPTargetArrayClass
implicit none
type(OMPTargetArrayDP) :: abc
integer, parameter :: Ntotal = 1000
integer :: i, Nsum

call abc%resize(Ntotal)

! initialize values
!$omp target teams distribute parallel do map(always, from:abc%array)
do i = 1, Ntotal
  abc%array(i) = i
enddo

! do a sum
Nsum = 0
!$omp target teams distribute parallel do reduction(+: Nsum)
do i = 1, Ntotal
  Nsum = Nsum + abc%array(i)
enddo

write(*,*) "Nsum = ", Nsum

if (Nsum /= 500500) stop 1
!write(*,*) "end of subroutine"
end subroutine test

program main
call test()
!write(*,*) "end of program"
end program main
