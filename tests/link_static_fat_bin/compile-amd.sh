clang++ -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx906 -c classA.cpp
rm -f mylib.a
llvm-ar qc mylib.a classA.o
llvm-ranlib mylib.a
clang++ -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx906 main.cpp mylib.a
./a.out
