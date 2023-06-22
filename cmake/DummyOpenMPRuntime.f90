module omp_lib
contains
function omp_get_num_threads()
  implicit none
  integer omp_get_num_threads
  omp_get_num_threads = 1
end function omp_get_num_threads

function omp_get_num_teams()
  implicit none
  integer omp_get_num_teams
  omp_get_num_teams = 1
end function omp_get_num_teams

function omp_get_thread_num()
  implicit none
  integer omp_get_thread_num
  omp_get_thread_num = 0
end function omp_get_thread_num

function omp_get_team_num()
  implicit none
  integer omp_get_team_num
  omp_get_team_num = 0
end function omp_get_team_num
end module
