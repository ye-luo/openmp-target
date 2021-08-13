clang++ -fopenmp -fopenmp-targets=nvptx64 -c foo.cpp
clang++ -fopenmp -c boo.cpp
clang++ -fopenmp -fopenmp-targets=nvptx64 main.cpp boo.o foo.o 
#nvlink fatal   : Could not open input file '/tmp/foo-7e0588.cubin'
#clang-14: error: nvlink command failed with exit code 1 (use -v to see invocation)
