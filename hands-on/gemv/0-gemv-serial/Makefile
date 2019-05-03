include ../../make.inc

name=gemv-serial
${name}.x: ${name}.cpp
	${CXX} -std=c++11 -Drestrict=__restrict__ ${CXX_FLAGS} -o $@ -I ../../common $<

.PHONY : clean
clean :
	rm -f *.x
