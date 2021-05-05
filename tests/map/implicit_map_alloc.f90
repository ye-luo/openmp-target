program main
  implicit none
  type foobar
    real(8),allocatable,dimension(:) :: foo, bar
  end type
  type(foobar) :: this
  integer, parameter :: n = 1024

  allocate(this%foo(n), this%bar(n))
  this%foo = 1d0
  !$omp target enter data map(to:this%foo) map(alloc:this%bar)

  !$omp target
  this%bar = 3d0
  !$omp end target

  !$omp target update from(this%bar)

  if (all(this%foo < this%bar)) then
     print *,"Success!"
  else
     stop 1
  endif

end program main
