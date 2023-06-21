program test_use_device_ptr
  implicit none
  double precision :: alpha
  integer, parameter :: lda = 10
  double precision, allocatable :: mat(:, :)

  allocate(mat(lda, lda))
  call dgemm(lda, mat)

  contains
    subroutine dgemm(lda, a)
      implicit none
      integer :: lda
      double precision, target:: a(lda,lda) ! need target attribute to use c_loc
      !$omp target data use_device_ptr(a) map(a)
        !call cublas_dgemm('T','N',M,N,K,alpha,c_loc(A),LDA,c_loc(b) +,LDB,beta,c_loc(c),LDC)
      !$omp end target data
    end subroutine
end program
