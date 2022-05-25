# GCC requres UDR
```
g++ -O3 -fopenmp -foffload=disable array_reduction.cpp && ./a.out
g++ -O3 -fopenmp -foffload=nvptx-none -foffload-options="-lm -latomic" array_reduction.cpp && ./a.out
```

# Clang allows both with and without UDR
```
clang++ -O3 -fopenmp array_reduction.cpp && ./a.out
clang++ -O3 -fopenmp -fopenmp-targets=nvptx64 array_reduction.cpp && ./a.out
clang++ -O3 -fopenmp -D__NO_UDR array_reduction.cpp && ./a.out
clang++ -O3 -fopenmp -fopenmp-targets=nvptx64 -D__NO_UDR array_reduction.cpp && ./a.out
```

# NVHPC disallow UDR
```
nvc++  -O3 -mp -D__NO_UDR array_reduction.cpp # doesn't work
nvc++  -O3 -mp=gpu -D__NO_UDR array_reduction.cpp # doesn't work
```
