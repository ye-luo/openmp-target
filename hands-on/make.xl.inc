CXX=xlC_r
CXX_FLAGS=-g -O3 -qsmp=omp
CXX_OFFLOAD_FLAGS=-qoffload

FC=xlf90_r
FC_FLAGS=${CXX_FLAGS}
FC_OFFLOAD_FLAGS=${CXX_OFFLOAD_FLAGS}
