include ../../make.inc

name=gemv-omp-target-teams
${name}.x: ${name}.cpp
	${CXX} -std=c++11 -Drestrict=__restrict__ ${CXX_FLAGS} ${CXX_OFFLOAD_FLAGS} -o $@ -I ../../common $<

.PHONY : clean
clean :
	rm -f *.x
