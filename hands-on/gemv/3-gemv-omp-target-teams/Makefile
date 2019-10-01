include ../../make.inc

name=gemv-omp-target-teams

all: ${name}.x ${name}.f

${name}.x: ${name}.cpp
	${CXX} -std=c++11 -Drestrict=__restrict__ ${CXX_FLAGS} ${CXX_OFFLOAD_FLAGS} -o $@ -I ../../common $<

${name}.f: ${name}.f90
	${FXX}  ${FXX_FLAGS} ${FXX_OFFLOAD_FLAGS}  -o $@ $<

.PHONY : clean
clean :
	rm -f *.x *.f
