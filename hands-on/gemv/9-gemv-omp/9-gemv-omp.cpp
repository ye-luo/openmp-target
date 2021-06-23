#define N 2
#include "timer.h"

// Base code from 1-gemv-omp.cpp                                                                                                                             

template<typename T> // Creates a template type T to allow passing a data type as a parameter                                                                
void gemv(int n, T alpha, const T* __restrict__ A, const T* __restrict__ V, T* __restrict__ Vout)
{
//#pragma omp parallel for // No parallel for vanilla code                                                                                                   
  for (int row = 0; row < n; row++)
  { // Multiplies input matrix A with vector V and returns resulting vector in Vout                                                                          
    T sum                       = T(0); // Initialize sum                                                                                                    
    const T* __restrict__ A_row = A + row * n;
    for (int col = 0; col < n; col++) //                                                                                                                     
      {
        const T* __restrict__ V_col = V + col * n;
        sum += A_row[col] * V_col[row];
        std::cout << "Sum[" << row << "," << col << "]: " << sum << "\n";
        std::cout << "Puts sum in here.\n";
        Vout[row + col] = sum * alpha;
      }
    std::cout << "alpha: " << alpha << "\n";
    // Vout[row] = sum * alpha;                                                                                                                              
  }
}

template<class T>
T* allocate(size_t n)
{ // Creates matrix or vector                                                                                                                                
  T* ptr = new T[n]; // Creates a pointer to matrix of type T                                                                                                
  std::fill_n(ptr, 2, T(1)); // ptr is the pointer to the matrix, _n is size of vector,                                                                      
  //n in the parameters is how many values from start value to fill, T(1) is the value                                                                       
  return ptr; // returns pointer to matrix                                                                                                                   
}

template<class T>
void deallocate(T* ptr, size_t n)
{ // Frees up matrix data                                                                                                                                    
  delete[] ptr;
}

int main()
{
  auto* A    = allocate<float>(N * N); // Creates matrix A                                                                                                   
  auto* V    = allocate<float>(N * N); // Created vector V, now creates matrix V                                                                             
  auto* Vout = allocate<float>(N * N); // Created vector Vout, now creates matrix Vout                                                                       

  // Print matrix A                                                                                                                                          
  std::cout << "Matrix A: ";
  for(int i = 0; i < N * N; i++)
    std::cout << A[i];

  std::cout << "\n";

  std::cout << "Matrix V: ";
  for(int i = 0; i < N * N; i++)
    std::cout << V[i];

  std::cout << "\n";

    Timer local("GEMV");
    gemv(N, 1.0f, A, V, Vout);


  for (int i = 0; i < N *  N; i++)
    if (Vout[i] != N)
      { // Checks if resulting matrix is all N, so this checks if Vout is all 4 if both matrices are same                                                    
      std::cerr << "Vout[" << i << "] != " << N << ", wrong value is " << Vout[i] << std::endl;
      break;
    }

  std::cout << "Matrix Vout: ";
  for(int i = 0; i < N * N; i++)
    std::cout << Vout[i];

  std::cout << "\n";

  deallocate(A, N * N);
  deallocate(V, N * N);
  deallocate(Vout, N * N);
}
