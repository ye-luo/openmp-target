program test_omp
  use iso_c_binding, only: c_associated, c_loc, c_ptr
  use omp_lib
  implicit none
  integer, parameter :: Nteams = 3
  type(c_ptr) :: ptr_list(Nteams)
  integer :: team_ID(Nteams)
  real*4, target :: a
  integer :: i,j

  !$pragma omp target teams distribute num_teams(Nteams) private(a) map(from:ptr_list, team_ID)
  do i=1, Nteams
    team_ID(i) = omp_get_team_num();
    ptr_list(i) = c_loc(a)
  enddo

  write(*,*) "host pointer = %p\n"
  do i=1, Nteams-1
    do j=1, Nteams
      if(team_ID(i) /= team_ID(j) .and. c_associated(ptr_list(i), ptr_list(j))) then
        write(*,*) "ERROR identical pointer[%d] = %p, team id %d and %d\n";
      endif
    enddo
  enddo
end program
