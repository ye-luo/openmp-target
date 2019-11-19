include ../../make.inc

name=gemv-omp-target-reduction

all: ${name}.x ${name}-f.x

${name}.x: ${name}.cpp
	${CXX} -std=c++11 ${CXX_FLAGS} ${CXX_OFFLOAD_FLAGS} -o $@ -I ../../common $<

${name}-f.x: ${name}.f90
	${FC}  ${FC_FLAGS} ${FC_OFFLOAD_FLAGS}  -o $@ $<

.PHONY : clean
clean :
	rm -f *.x
