program test_omp
  use iso_c_binding, only: c_associated, c_loc, c_ptr, c_long
  implicit none
  integer, parameter :: Nteams = 3
  integer, parameter :: Nthreads = 3
  integer, parameter :: Ntot = Nteams * Nthreads
  type(c_ptr) :: ptr_list(Ntot)
  integer :: team_ID(Ntot)
  integer :: thread_ID(Ntot)
  real*4, target :: a
  integer :: i,j
  integer(c_long) :: ptr_val
  integer, external :: omp_get_team_num, omp_get_thread_num

  !$omp target teams distribute parallel do num_teams(Nteams) thread_limit(Nthreads) private(a) &
  !$omp map(from:ptr_list, team_ID, thread_ID)
  do i=1, Ntot
    team_ID(i) = omp_get_team_num();
    thread_ID(i) = omp_get_thread_num();
    ptr_list(i) = c_loc(a)
  enddo

  ptr_val = transfer(c_loc(a), ptr_val)
  write(*,*) "host pointer = ", ptr_val
  do i=1, Ntot-1
    ptr_val = transfer(ptr_list(i), ptr_val)
    do j=i+1, Ntot
      if((team_ID(i) /= team_ID(j) .or. thread_ID(i) /= thread_ID(j)) .and. c_associated(ptr_list(i), ptr_list(j))) then
        write(*,*) "WARNING identical pointer = ", ptr_val, &
                 & " (team,thread) id (", team_ID(i), ",", thread_ID(i), ")", &
                 & " and (", team_ID(j), ",", thread_ID(j), ")";
      endif
    enddo
  enddo
end program
