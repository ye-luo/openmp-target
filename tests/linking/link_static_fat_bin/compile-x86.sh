clang++ -fopenmp -fopenmp-targets=x86_64-pc-linux-gnu -c classA.cpp
rm -f libmy.a
ar qc libmy.a classA.o
ranlib libmy.a
clang++ -fopenmp -fopenmp-targets=x86_64-pc-linux-gnu main.cpp -L. -lmy
./a.out
