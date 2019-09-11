include ../../make.inc

name=gemv-omp-target-many-matrices
${name}.x: ${name}.cpp
	${CXX} -std=c++11 ${CXX_FLAGS} ${CXX_OFFLOAD_FLAGS} -o $@ -I ../../common $<

.PHONY : clean
clean :
	rm -f *.x
