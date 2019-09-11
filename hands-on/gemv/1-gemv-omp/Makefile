include ../../make.inc

name=gemv-omp
${name}.x: ${name}.cpp
	${CXX} -std=c++11 ${CXX_FLAGS} -o $@ -I ../../common $<

.PHONY : clean
clean :
	rm -f *.x
