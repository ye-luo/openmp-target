CXX=xlC_r
CXX_FLAGS="-qsmp=omp -qoffload"

$CXX $CXX_FLAGS -c a.cpp
$CXX $CXX_FLAGS -c b.cpp
$CXX $CXX_FLAGS main.cpp a.o b.o
