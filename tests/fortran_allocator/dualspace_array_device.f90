subroutine test
use dualspace
implicit none
type(dualspace_double_type) :: abc
real(8), dimension(:), pointer :: abc_data 
integer, parameter :: Ntotal = 1000
integer :: i, Nsum

call abc%resize(Ntotal)

! initialize values
abc_data => abc%data()
!$omp target teams distribute parallel do map(always, from:abc_data)
do i = 1, Ntotal
  abc_data(i) = i
enddo

! do a sum
Nsum = 0
!$omp target teams distribute parallel do reduction(+: Nsum)
do i = 1, Ntotal
  Nsum = Nsum + abc_data(i)
enddo

write(*,*) "Nsum = ", Nsum

if (Nsum /= 500500) stop 1
!write(*,*) "end of subroutine"
end subroutine test

program main
call test()
!write(*,*) "end of program"
end program main
