CXX=icpx
OFFLOAD_FLAGS=-fiopenmp -fopenmp-targets=spir64

.PHONY: clean

a.out: main.cpp data.o
	${CXX} ${OFFLOAD_FLAGS} main.cpp data.o
data.o: data.cpp data.hpp
	${CXX} ${OFFLOAD_FLAGS} -c data.cpp

clean:
	rm data.o a.out
