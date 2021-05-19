Bug report
https://bugs.llvm.org/show_bug.cgi?id=42393

```
$ icpx -fiopenmp -fopenmp-targets=spir64 debug.cpp

$ OMP_NUM_THREADS=2 OMP_TARGET_OFFLOAD=MANDATORY ./a.out
tid = 1
  0  1  2  3
tid = 0
  0  1  2  3

$ OMP_NUM_THREADS=2 OMP_TARGET_OFFLOAD=DISABLED ./a.out
tid = 0
  0  1  0  0
tid = 1
  0  0  2  3

$ icpx -fiopenmp debug.cpp
tid = 0
  0  1  0  0
tid = 1
  0  0  2  3
```
