CC=gcc
CC_FLAGS="-O3 -fopenmp -foffload=nvptx-none"

for name in *.c
do
  $CC $CC_FLAGS $name
  ./a.out
done
