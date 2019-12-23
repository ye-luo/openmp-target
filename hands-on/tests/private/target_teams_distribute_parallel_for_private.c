#include <stdio.h>
#include <omp.h>

int main()
{
  const int Nteams = 3;
  const int Nthreads = 3;
  const int Ntot = Nteams*Nthreads;
  void* pointer[Ntot];
  int team_ID[Ntot];
  int thread_ID[Ntot];
  float a;
  #pragma omp target teams distribute parallel for num_teams(Nteams) thread_limit(Nthreads) private(a) map(from:pointer[:Ntot], team_ID[:Ntot], thread_ID[:Ntot])
  for(int i = 0; i<Ntot; i++)
  {
    team_ID[i] = omp_get_team_num();
    thread_ID[i] = omp_get_thread_num();
    pointer[i] = &a;
  }

  printf("host pointer = %p\n", &a);
  for(int i = 0; i<Ntot-1; i++)
    for(int j = i+1; j<Ntot; j++)
      if((team_ID[i] != team_ID[j] || thread_ID[i]!=thread_ID[j]) && pointer[i] == pointer[j])
        printf("ERROR identical pointer = %p, (team,thread) id (%d,%d) and (%d,%d)\n", pointer[i], team_ID[i], thread_ID[i], team_ID[j], thread_ID[j]);
  return 0;
}
