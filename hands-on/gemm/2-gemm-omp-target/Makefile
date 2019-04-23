name=gemm-omp-target
${name}.x: ${name}.cpp
	clang++ -std=c++11 -Drestrict=__restrict__ -fopenmp -fopenmp-targets=nvptx64-nvida-cuda -O3 -g -o $@ $<
