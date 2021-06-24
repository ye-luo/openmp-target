#define N 8192
#include "timer.h"

// Base code from 1-gemv-omp.cpp                                                                                                 

template<typename T> // Creates a template type T to allow passing a data type as a parameter                                    
void gemv(int n, T alpha, const T* __restrict__ A, const T* __restrict__ V, T* __restrict__ Vout)
{
  int index = 0;
 #pragma omp parallel for // No parallel for vanilla code                                                                        
  for (int row = 0; row < n; row++)
  { // Multiplies input matrix A with vector V and returns resulting vector in Vout                                              
    T sum                       = T(0); // Initialize sum                                                                        
    const T* __restrict__ A_row = A + row * n;
    for (int col = 0; col < n; col++) //                                                                                         
      {
        const T* __restrict__ V_col = V + col * n;
        sum += A_row[col] * V_col[row];
        // std::cout << "Sum[" << row << "," << col << "]: " << sum << "\n"; // Debugging                                        
        // std::cout << "Index: " << index << "\n"; // Debugging                                                                 
        Vout[index] = sum * alpha;
        index++; // Debugging                                                                                                 
      }
    // std::cout << "alpha: " << alpha << "\n"; // Debugging                                                                     
  }
}

template<class T>
T* allocate(size_t n)
{ // Creates matrix or vector                                                                                                    
  T* ptr = new T[n]; // Creates a pointer to matrix of type T                                                                    
  std::fill_n(ptr, n, T(1)); // ptr is the pointer to the matrix, _n is size of vector,                                          
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

    Timer local("GEMV");
    gemv(N, 1.0f, A, V, Vout);


  for (int i = 0; i < N *  N; i++)
    if (Vout[i] != N)
      { // Checks if resulting matrix is all N, so this checks if Vout is all 4 if both matrices are same                        
      std::cerr << "Vout[" << i << "] != " << N << ", wrong value is " << Vout[i] << std::endl;
      break;
    }
  
  deallocate(A, N * N);
  deallocate(V, N * N);
  deallocate(Vout, N * N);
}
