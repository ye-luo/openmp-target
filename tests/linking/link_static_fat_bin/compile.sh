clang++ -fopenmp -fopenmp-targets=nvptx64 -c classA.cpp
rm -f libmy.a
ar qc libmy.a classA.o
ranlib libmy.a
clang++ -fopenmp -fopenmp-targets=nvptx64 main.cpp libmy.a
./a.out
