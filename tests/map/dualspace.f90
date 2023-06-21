module dualspace
  use iso_c_binding
  use iso_fortran_env
  implicit none

  type dualspace_base_type
    character, dimension(:), pointer :: data_f => NULL ()
    integer(int64) :: data_length = 0
    type(c_ptr) :: data_ptr = c_null_ptr
    contains
      procedure :: resize_base
      final :: deallocate_data
  end type

  type, extends(dualspace_base_type) :: dualspace_double_type
    integer :: dims = 0
  contains
    procedure :: resize => resize_double
    procedure :: data => data_double
  end type

  type, extends(dualspace_base_type) :: dualspace_cplx_double_type
    integer :: dims = 0
  contains
    procedure :: resize => resize_cplx_double
    procedure :: data => data_cplx_double
  end type

contains
  subroutine resize_base(self, bytes)
    implicit none
    class(dualspace_base_type), intent(inout) :: self
    integer(int64), intent(in) :: bytes

    if (self%data_length .ne. bytes) then
      call deallocate_data(self)
      call allocate_data(self, bytes)
    endif

    self%data_ptr = C_LOC(self%data_f)
  end subroutine

  subroutine allocate_data(self, bytes)
    implicit none
    type(dualspace_base_type), intent(inout) :: self
    integer(int64), intent(in) :: bytes
    if (bytes > 0) then
      allocate(self%data_f(bytes))
      !$omp target enter data map(alloc: self%data_f)
      write(*,*) "allocate_data size ", bytes
    endif
    self%data_length = bytes
  end subroutine

  subroutine deallocate_data(self)
    implicit none
    type(dualspace_base_type), intent(inout) :: self
    if (self%data_length > 0) then
      write(*,*) "deallocate_data size ", self%data_length
      !$omp target exit data map(delete: self%data_f)
      deallocate(self%data_f)
    endif
    self%data_length = 0
  end subroutine

  subroutine resize_double(self, num)
    class(dualspace_double_type), intent(inout) :: self
    integer, intent(in) :: num
    real(real64) :: dummy
    call self%resize_base(num * sizeof(dummy))
    self%dims = num
  end subroutine

  subroutine resize_cplx_double(self, num)
    class(dualspace_cplx_double_type), intent(inout) :: self
    integer, intent(in) :: num
    complex(real64) :: dummy
    call self%resize_base(num * sizeof(dummy))
    self%dims = num
  end subroutine

  function data_double(self) result(res)
    class(dualspace_double_type), intent(inout) :: self
    real(real64), dimension(:), pointer :: res

    call C_F_POINTER(self%data_ptr, res, shape=[self%dims])
  end function

  function data_cplx_double(self) result(res)
    class(dualspace_cplx_double_type), intent(inout) :: self
    complex(real64), dimension(:), pointer :: res

    call C_F_POINTER(self%data_ptr, res, shape=[self%dims])
  end function
end module

subroutine fill_density(density)
  use dualspace, only: dualspace_double_type, dualspace_cplx_double_type
  implicit none
  type(dualspace_double_type), intent(inout) :: density
  real(8), dimension(:), pointer :: density_data
  integer, parameter :: test_size =20
  integer :: i

  call density%resize(test_size)
  density_data => density%data()
  write(*,*) "density_data size ", size(density_data)
  do i = 1, test_size
    density_data(i) = 1.
  enddo
  !$omp target update to(density_data)
  !$omp target teams distribute parallel do map(always, from: density_data)
  do i = 1, test_size
    density_data(i) = density_data(i) + i * 1.
  enddo

  if (density_data(3).ne.4.) stop 1
end subroutine

program abc
  use dualspace, only: dualspace_double_type, dualspace_cplx_double_type
  implicit none

  type(dualspace_double_type) :: density, density2
  real(8), dimension(:), pointer :: density_data
  call density%resize(10)
  density_data => density%data()
  write(*,*) "density_data size ", size(density_data)

  call fill_density(density2)
  density_data => density2%data()
  write(*,*) "density_data(3) should be 3. Current value ", density_data(3)

  block
    type(dualspace_cplx_double_type) :: wf
    complex(8), dimension(:), pointer :: wf_data
    call wf%resize(30)
    wf_data =>  wf%data()
    write(*,*) "wf_data size ", size(wf_data)
  end block
end program
