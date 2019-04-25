name=gemv-omp-target-many-matrices
${name}.x: ${name}.cpp
	clang++ -std=c++11 -Drestrict=__restrict__ -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -O3 -g -o $@ $<
