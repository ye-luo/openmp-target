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
