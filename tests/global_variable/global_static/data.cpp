#include "data.hpp"

#pragma omp declare target
template <>
const float engine<float>::params[4] = {1.0f, 2.0f, 3.0f, 4.0f};

template <>
const double engine<double>::params[4] = {1.0, 2.0, 3.0, 4.0};
#pragma omp end declare target
