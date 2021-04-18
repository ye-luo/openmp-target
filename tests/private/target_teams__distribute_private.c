#include <stdio.h>
#include <omp.h>

int main()
{
  const int Nteams = 2;
  void* pointer[Nteams];
  int team_ID[Nteams];
  float a;
  float* a_p;
  #pragma omp target teams num_teams(Nteams) map(from:pointer[:Nteams], a_p, team_ID[:Nteams])
  {
    a_p = &a;
    #pragma omp distribute private(a)
    for(int i = 0; i<Nteams; i++)
    {
      team_ID[i] = omp_get_team_num();
      pointer[i] = &a;
    }
  }

  printf("host pointer = %p\n", &a);
  printf("device global pointer = %p\n", a_p);
  for(int i = 0; i<Nteams; i++)
    printf("pointer[%d] = %p, team id %d\n", i, pointer[i], team_ID[i]);
  return 0;
}
