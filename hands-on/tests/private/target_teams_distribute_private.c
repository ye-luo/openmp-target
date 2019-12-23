#include <stdio.h>
#include <omp.h>

int main()
{
  const int Nteams = 3;
  void* pointer[Nteams];
  int team_ID[Nteams];
  float a;
  #pragma omp target teams distribute num_teams(Nteams) private(a) map(from:pointer[:Nteams], team_ID[:Nteams])
  for(int i = 0; i<Nteams; i++)
  {
    team_ID[i] = omp_get_team_num();
    pointer[i] = &a;
  }

  printf("host pointer = %p\n", &a);
  for(int i = 0; i<Nteams-1; i++)
    for(int j = i+1; j<Nteams; j++)
      if(team_ID[i] != team_ID[j] && pointer[i] == pointer[j])
        printf("ERROR identical pointer[%d] = %p, team id %d and %d\n", i, pointer[i], team_ID[i], team_ID[j]);
  return 0;
}
