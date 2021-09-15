clang++ -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx906 -c classA.cpp
rm -f libmy.a
llvm-ar qc libmy.a classA.o
llvm-ranlib libmy.a
clang++ -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx906 main.cpp libmy.a
./a.out
