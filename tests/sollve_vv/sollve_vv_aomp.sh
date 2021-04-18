git clone https://github.com/SOLLVE/sollve_vv.git
# this is so we can avoid hanging
sed -i s/timeout/"timeout -s 9"/ sollve_vv/sys/scripts/run_test.sh
cd sollve_vv
OFFLOAD_FLAG="-fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx906"
make OMP_VERSION=4.5 CC="clang -std=c99 $OFFLOAD_FLAG" \
                     CXX="clang++ -std=c++11 $OFFLOAD_FLAG" \
                     FC="flang $OFFLOAD_FLAG" \
     VERBOSE_TESTS=1 VERBOSE=1 LOG=1 LOG_ALL=1 all 
make report_summary &> 45.out
make tidy
make OMP_VERSION=5.0 CC="clang -std=c99 -fopenmp-version=50 $OFFLOAD_FLAG" \
                     CXX="clang++ -std=c++11 -fopenmp-version=50 $OFFLOAD_FLAG" \
                     FC="flang $OFFLOAD_FLAG" \
     VERBOSE_TESTS=1 VERBOSE=1 LOG=1 LOG_ALL=1 all
make report_summary &> 50.out
cd ..
