#include <iostream>
#include <omp.h>
#define NTEAM 32
#define TEAM_SIZE 128

template<class T>
void compute_prefactor(int team_id, T base[2])
{
  base[0] = team_id;
  base[1] = team_id * 2;
}

bool failed = false;

template<class T>
void test_omp_pteam_mem_alloc()
{
  T sum[NTEAM];
  #pragma omp target teams distribute map(from:sum[:NTEAM])
  for(int team_id = 0; team_id < NTEAM; team_id++)
  {
    T local_sum = 0;
    T base[2];
    #pragma omp allocate(base) allocator(omp_pteam_mem_alloc)
    compute_prefactor(team_id, base);
    #pragma omp parallel for reduction(+: local_sum)
    for(int tid = 0; tid < TEAM_SIZE; tid++)
      local_sum += base[0] + tid;
    sum[team_id] = local_sum;
  }
  for(int team_id = 0; team_id < NTEAM; team_id++)
    if (sum[team_id] != team_id * TEAM_SIZE + (TEAM_SIZE -1) * TEAM_SIZE / 2 )
    {
      std::cout << "sum[" << team_id << "] = " << sum[team_id] << " ref " << team_id * TEAM_SIZE + (TEAM_SIZE -1) * TEAM_SIZE / 2 << std::endl;
      failed = true;
    }
}

int main()
{
  test_omp_pteam_mem_alloc<int>();
  return failed;
}
