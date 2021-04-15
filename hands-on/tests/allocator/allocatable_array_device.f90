module OMPTargetArrayClass
implicit none
    type, public :: OMPTargetArrayDP
      real(kind = 8), dimension(:), allocatable :: array
    contains
      ! here come the methods
      procedure, public :: alloc => allocateArray
      final :: destructor
    end type OMPTargetArrayDP
contains

    subroutine allocateArray(this, array_size)
      implicit none
      class(OMPTargetArrayDP) :: this
      integer array_size
      if (.not. allocated(this%array)) then
        allocate(this%array(array_size))
        !$omp target enter data map(alloc: this%array)
      else if (size(this%array) /= array_size) then
        !$omp target exit data map(delete: this%array)
        deallocate(this%array)
        allocate(this%array(array_size))
        !$omp target enter data map(alloc: this%array)
      endif
    end subroutine

    subroutine destructor(this)
      implicit none
      Type(OMPTargetArrayDP) :: this
      !$omp target exit data map(delete: this%array)
      ! Do whatever needs doing in the destructor
      write(*,*) "calling destructor"
    end subroutine destructor
end module OMPTargetArrayClass


subroutine test
use OMPTargetArrayClass
type(OMPTargetArrayDP) :: abc
call abc%alloc(10)
write(*,*) "end of subroutine"
end subroutine test

program main
call test()
write(*,*) "end of program"
end program main
