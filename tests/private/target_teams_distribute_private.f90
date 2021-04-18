program test_omp
  use iso_c_binding, only: c_associated, c_loc, c_ptr, c_long
  use omp_lib
  implicit none
  integer, parameter :: Nteams = 3
  type(c_ptr) :: ptr_list(Nteams)
  integer :: team_ID(Nteams)
  real*4, target :: a
  integer :: i,j
  integer(c_long) :: ptr_val

  !$omp target teams distribute num_teams(Nteams) private(a) map(from:ptr_list, team_ID)
  do i=1, Nteams
    team_ID(i) = omp_get_team_num();
    ptr_list(i) = c_loc(a)
  enddo

  ptr_val = transfer(c_loc(a), ptr_val)
  write(*,*) "host pointer = ", ptr_val
  do i=1, Nteams-1
    ptr_val = transfer(ptr_list(i), ptr_val)
    do j=i+1, Nteams
      if(team_ID(i) /= team_ID(j) .and. c_associated(ptr_list(i), ptr_list(j))) then
        write(*,*) "ERROR identical pointer = ", ptr_val, " team id ", team_ID(i), " and ", team_ID(j);
      endif
    enddo
  enddo
end program
