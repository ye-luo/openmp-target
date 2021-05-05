Case 1
```
nvfortran -cuda noomp.f90
./a.out
```
good

Case 2
```
nvfortran -cuda -mp=gpu noomp.f90
./a.out
```
SegFault

Case 3
```
nvfortran -cuda -mp=gpu omp_below.f90
```
Compiler error
```
NVFORTRAN-S-1050-Non-tightly nested loop in cuf kernels do at nest 1 (omp_below.f90: 18)
NVFORTRAN-S-0155-Kernel region ignored; no parallel loops  (omp_below.f90: 17)
  0 inform,   0 warnings,   2 severes, 0 fatal for repro
NVFORTRAN-S-1058-Call to PGI runtime function not supported - pgf90_dev_copyout (omp_below.f90: 28)
```

Case 4
```
nvfortran -cuda -mp=gpu omp_above.f90
```
Compiler error
```
NVFORTRAN-S-1058-Call to PGI runtime function not supported - pgf90_dev_copyout (omp_above.f90: 20)
```
