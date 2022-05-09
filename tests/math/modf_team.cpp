#include <iostream>
#include <cmath>
#include <limits>

template<typename T, typename TRESIDUAL>
inline void getSplineBound(T x, TRESIDUAL& dx, int& ind, int nmax)
{
  // lower bound
  if (x < 0)
  {
    ind = 0;
    dx  = T(0);
  }
  else
  {
#if defined(USE_FLOOR)
    T ipart = std::floor(x);
    dx  = x - ipart;
#else
    T ipart;
    dx  = std::modf(x, &ipart);
#endif
    ind = static_cast<int>(ipart);
    // upper bound
    if (ind > nmax)
    {
      ind = nmax;
      dx  = T(1) - std::numeric_limits<T>::epsilon();
    }
  }
}

int main()
{
  using T = float;
  T x = 1.25;
  T dx = 0;
  int ind = 0;
  #pragma omp target map(from: dx, ind)
  {
    getSplineBound(x, dx, ind, 10);
  }

  if(x != T(dx + ind))
  {
    std::cout << "Error x = " << x << " dx = " << dx << " ind " << ind << std::endl;
    return 1;
  }

  constexpr int N = 100;
  T x_arr[N];
  T dx_arr[N];
  int ind_arr[N];
  for (int i = 0; i < N; i++)
    x_arr[i] = (i+1)*0.25;

  #pragma omp target teams distribute map(to: x_arr[:N]) map(from: dx_arr[:N], ind_arr[:N])
  for (int i = 0; i < N; i++)
    getSplineBound(x_arr[i], dx_arr[i], ind_arr[i], 24);

  for (int i = 0; i < N-1; i++)
    if(x_arr[i] != T(dx_arr[i] + ind_arr[i]))
    {
      std::cout << "Error team = " << i << " x = " << x_arr[i] << " dx = " << dx_arr[i] << " ind " << ind_arr[i] << std::endl; 
      return 1;
    }

  //special case
  {
    const int i = N - 1;
    if (ind_arr[i] != 24)
    {
      std::cout << "Error team = " << i << " x = " << x_arr[i] << " dx = " << dx_arr[i] << " ind " << ind_arr[i] << std::endl; 
      return 1;
    }
  }
}
