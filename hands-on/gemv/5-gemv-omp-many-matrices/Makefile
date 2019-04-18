name=gemv-omp-many-matrices
${name}.x: ${name}.cpp
	clang++ -std=c++11 -Drestrict=__restrict__ -fopenmp -g -o $@ $<
