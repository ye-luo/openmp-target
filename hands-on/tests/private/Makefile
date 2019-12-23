include ../../make.inc

name=target_teams_distribute_private

all_targets=
ifdef ENABLE_C
  all_targets += ${name}.c.x
endif
ifdef ENABLE_CXX
  all_targets += ${name}.cpp.x
endif
ifdef ENABLE_FC
  all_targets += ${name}.f.x
endif

all: ${all_targets}

${name}.cpp.x: ${name}.cpp
	${CXX} -std=c++11 ${CXX_FLAGS} ${CXX_OFFLOAD_FLAGS} -o $@ -I ../../common $< && ./$@

${name}.c.x: ${name}.c
	${CC} -std=c99 ${CC_FLAGS} ${CC_OFFLOAD_FLAGS} -o $@ -I ../../common $< && ./$@

${name}.f.x: ${name}.f90
	${FC}  ${FC_FLAGS} ${FC_OFFLOAD_FLAGS}  -o $@ $< && ./$@

.PHONY : clean
clean :
	rm -f *.x
