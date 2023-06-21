program main
  implicit none
  type foobar
    real(8), dimension(:), pointer :: foo, bar
  end type
  type(foobar) :: this
  integer, parameter :: n = 1024
  integer :: i
  real(8), dimension(:), pointer :: bar_ptr

  allocate(this%foo(n), this%bar(n))
  this%foo = 1d0
  !$omp target enter data map(to:this%foo) map(alloc:this%bar)

  bar_ptr => this%bar
  !$omp target teams distribute parallel do
  do i = 1,n
    bar_ptr(i) = 3d0
  enddo
  !$omp end target teams distribute parallel do

  !$omp target update from(this%bar)

  if (all(this%foo < this%bar)) then
     print *,"Success!"
  else
     write(*,*) this%foo(3), this%bar(1), this%bar(2)
     stop 1
  endif

end program main
