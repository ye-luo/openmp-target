name=gemv-omp-target-reduction
${name}.x: ${name}.cpp
	clang++ -std=c++11 -Drestrict=__restrict__ -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -g -o $@ $<
