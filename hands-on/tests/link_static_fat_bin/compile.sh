clang++ -fopenmp -fopenmp-targets=nvptx64 -c classA.cpp
rm -f mylib.a
ar qc mylib.a classA.o
ranlib mylib.a
clang++ -fopenmp -fopenmp-targets=nvptx64 main.cpp mylib.a
./a.out
