module OMPTargetArrayClass
implicit none
    type, public :: OMPTargetArrayDP
      real(kind = 8), dimension(:), allocatable :: array
    contains
      ! here come the methods
      procedure, public :: resize => resizeDPArray
      procedure, private :: alloc => allocateDPArray
      procedure, private :: free => freeDPArray
      final :: destructDPArray
    end type OMPTargetArrayDP
contains

    subroutine resizeDPArray(this, array_size)
      implicit none
      class(OMPTargetArrayDP) :: this
      integer, intent(in) :: array_size
      if (.not. allocated(this%array)) then
        call this%alloc(array_size)
      else if (size(this%array) /= array_size) then
        call this%free()
        call this%alloc(array_size)
      endif
    end subroutine

    subroutine allocateDPArray(this, array_size)
      implicit none
      class(OMPTargetArrayDP) :: this
      integer, intent(in) :: array_size
      allocate(this%array(array_size))
      !$omp target enter data map(alloc: this%array)
    end subroutine

    subroutine freeDPArray(this)
      implicit none
      class(OMPTargetArrayDP) :: this
      !$omp target exit data map(delete: this%array)
      deallocate(this%array)
    end subroutine

    subroutine destructDPArray(this)
      implicit none
      Type(OMPTargetArrayDP) :: this
      ! Do whatever needs doing in the destructor
      !write(*,*) "calling destructor"
      if (allocated(this%array)) call this%free()
    end subroutine destructDPArray
end module OMPTargetArrayClass

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
