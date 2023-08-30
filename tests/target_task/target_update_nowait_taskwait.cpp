//////////////////////////////////////////////////////////////////////////////////////
// This file is distributed under the University of Illinois/NCSA Open Source License.
// See LICENSE file in top directory for details.
//
// Copyright (c) 2023 QMCPACK developers.
//
// File developed by: Ye Luo, yeluo@anl.gov, Argonne National Laboratory
//
// File created by: Ye Luo, yeluo@anl.gov, Argonne National Laboratory
//////////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include <vector>

const int num_sections = 1;
const int section_size = 100;
constexpr int array_size = num_sections * section_size;

int main(int argc, char** argv)
{
  //std::vector<int, OMPallocator<int>> array(array_size, 1);
  std::vector<int> array(array_size, 1);
  int* array_ptr = array.data();
  #pragma omp target enter data map(alloc:array_ptr[:array_size])
  for (int offset = 0; offset < array_size; offset += section_size)
  {
    #pragma omp target update from(array_ptr[offset:section_size]) nowait
  }
  #pragma omp taskwait
  #pragma omp target exit data map(delete:array_ptr[:array_size])
}
