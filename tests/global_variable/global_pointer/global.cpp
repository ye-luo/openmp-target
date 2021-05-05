#include "global.h"

#pragma omp declare target
int * device_arr;
#pragma omp end declare target
