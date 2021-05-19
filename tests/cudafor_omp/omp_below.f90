module test
  implicit none
  contains
    SUBROUTINE repro()
      use cudafor
      IMPLICIT NONE
      integer, device, allocatable :: nh_d2(:),ityp_d2(:)
      integer :: na,i
      integer :: nat,npw,ierr
      integer :: np,nh_np,ih
      nat = 1
      npw = 1050
      allocate(ityp_d2(1:nat))
      ityp_d2 = 5
      allocate(nh_d2(1:1000))
      nh_d2 = 3
      !$cuf kernel do(2) <<<*,*>>>
      DO na =1, nat
         DO i = 1, npw
            np = ityp_d2(na)
            nh_np = nh_d2(np)
         ENDDO
      ENDDO

      !$omp target teams distribute parallel do collapse(2)
      DO na =1, nat
         DO i = 1, npw
            np = ityp_d2(na)
            nh_np = nh_d2(np)
         ENDDO
      ENDDO

      deallocate(ityp_d2,nh_d2)
      !
    END SUBROUTINE repro
end module test

program main
   use test
   implicit none
   call repro
end program
