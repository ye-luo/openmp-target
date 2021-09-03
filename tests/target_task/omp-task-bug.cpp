#include <iostream>
#include <numeric>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_thread_num() { return 1; }
int omp_get_max_threads() { return 1; }
#endif

template<typename T>
struct MyProblem
{
  int M    = 16;
  int N    = 16;
  int K    = 32;
  int Size = 0;
  int IP   = 0;
  T* V     = nullptr;
  T* W     = nullptr;

  explicit MyProblem(int np) : Size(M * N * K / np)
  {
    M            = M / np;
    size_t bytes = Size * sizeof(T);
    auto* v_ptr  = (T*)aligned_alloc(64, bytes);
    auto* w_ptr  = (T*)aligned_alloc(64, bytes);

#pragma omp target enter data map(alloc : v_ptr [0:Size], w_ptr [0:Size])

    V = v_ptr;
    W = w_ptr;

#pragma omp target enter data map(to : this [0:1])
  }

  ~MyProblem()
  {
    auto* v_ptr = V;
    auto* w_ptr = W;

#pragma omp target exit data map(delete : this [0:1])

#pragma omp target exit data map(delete : v_ptr[:Size], w_ptr[:Size])

    free(W);
    free(V);
  }

  void setV(int ip)
  {
    IP = ip;
    std::iota(V, V + Size, T(ip * Size));
  }

  void update()
  {
    // v_ptr and w_ptr are shared as a task is created
    auto* v_ptr = V;
    auto* w_ptr = W;
#pragma omp target teams distribute collapse(2) map(always, to : v_ptr[:Size]) nowait depend(out : w_ptr[:Size])
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < N; ++j)
      {
#pragma omp parallel for
        for (int k = 0; k < K; ++k)
        {
          int ijk    = i * N * K + j * K + k;
          w_ptr[ijk] = 0.1f + v_ptr[ijk];
        }
      }

#pragma omp target update nowait depend(inout : w_ptr[:Size]) from(w_ptr[:Size])

#if defined(INPLACE_TASKWAIT)
#pragma omp taskwait
#endif
  }

  void write() const
  {
    std::cout << "result: " << IP << std::endl;
    std::cout << "V[" << 0 << "] = " << V[0] << " " << W[0] << std::endl;
    std::cout << "V[" << Size / 2 << "] = " << V[Size / 2] << " " << W[Size / 2] << std::endl;
    std::cout << "V[" << Size - 1 << "] = " << V[Size - 1] << " " << W[Size - 1] << std::endl;
  }
};

int main(int argc, char** argv)
{
  const int np = omp_get_max_threads();

  std::vector<MyProblem<float>*> problems(np * 4);

#pragma omp parallel
  {
    int ip = omp_get_thread_num();

    for (int iw = 0; iw < 4; iw++)
    {
      int I       = ip * 4 + iw;
      problems[I] = new MyProblem<float>(np * 4);
      problems[I]->setV(I);
    }

    for (int iw = 0; iw < 4; iw++)
    {
      int I = ip * 4 + iw;
      problems[I]->update();
    }
  }

  /*
    for(int ip=0; ip<np*4; ++ip)
    {
      problems[ip]->write();
    }
  */
}
