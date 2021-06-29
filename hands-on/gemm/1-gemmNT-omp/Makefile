name=gemmNT-omp
${name}.x: ${name}.cpp
	clang++ -std=c++11 -Drestrict=__restrict__ -fopenmp -march=native -O3 -g -o $@ -I ../../common $<

.PHONY : clean
clean :
	rm -f *.x
