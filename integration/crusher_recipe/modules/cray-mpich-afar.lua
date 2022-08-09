--[[

    file cray-mpich-llvm module
    This is not from Cray.
]]--

conflict("mpiwrappers")
unload("PrgEnv-cray")
unload("PrgEnv-gnu")
unload("PrgEnv-amd")
unload("PrgEnv-cray-amd")

load("gcc")
load("afar")
load("craype")
load("cray-mpich")
load("cray-pals")

prepend_path("PATH", pathJoin(os.getenv("MPICH_DIR"), "bin"), ":")

setenv("MPICH_CC", "clang")
setenv("MPICH_CXX", "clang++")
setenv("MPICH_FC", "flang")
setenv("MPICH_F77", "flang")
setenv("MPICH_F90", "flang")

setenv("ROCM_PATH", pathJoin(os.getenv("OLCF_AFAR_ROOT")))
