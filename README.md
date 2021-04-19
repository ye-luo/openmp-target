A collection of OpenMP tests for C++ and Fortran compilers

Recipe example
```
mkdir build_gcc_omp
cd build_gcc_omp
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_Fortran_COMPILER=gfortran \
      -DCMAKE_CXX_FLAGS=-fopenmp -DCMAKE_Fortran_FLAGS=-fopenmp \
      ..
make -k -j 16
ctest
```

###
OpenMP offload compiler options
https://github.com/ye-luo/openmp-target/wiki/OpenMP-offload-compilers
