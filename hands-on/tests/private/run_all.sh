CC=gcc
CC_FLAGS="-O3 -fopenmp -foffload=nvptx-none"

#CC=clang
#CC_FLAGS="-O3 -fopenmp -fopenmp-targets=nvptx64"

for name in *.c
do
  echo Testing $name
  $CC $CC_FLAGS $name
  ./a.out
  echo
done
