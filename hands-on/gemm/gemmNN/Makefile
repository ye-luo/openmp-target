name=gemmNN
${name}.x: ${name}.cpp
	clang++ -std=c++11 -Drestrict=__restrict__ -fopenmp -fopenmp-targets=nvptx64-nvida-cuda -Xopenmp-target -march=sm_60 -O3 -g -o $@ -I ../../common $<

.PHONY : clean
clean :
	rm -f *.x
