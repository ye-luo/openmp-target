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

  private :: resize_base, allocate_data, deallocate_data
  private :: resize_double, resize_cplx_double
  private :: data_double, data_cplx_double
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
