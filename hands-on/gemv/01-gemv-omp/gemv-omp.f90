program gemv_omp

USE OMP_LIB

implicit none
integer,parameter:: N=64
real(8),allocatable :: A(:),V(:),Vout(:)
real(8) :: alpha=1.0
integer :: ti,tj,tk
integer :: err
integer :: val

!!starts here
call system_clock(ti,tk)
allocate(A(1:N*N),stat=err)
if(err/=0) print'(a30,i9,i3)', 'ERROR in allocation for A',err
allocate(V(1:N),stat=err)
if(err/=0) print'(a30,i9,i3)', 'ERROR in allocation for V',err
allocate(Vout(1:N),stat=err)
if(err/=0) print'(a30,i9,i3)', 'ERROR in allocation for Vout',err

A(:) = 1.0
V(:) = 1.0
call gemv(N,alpha,A,V,Vout)
do val=1,N
   if (int(Vout(val)) .NE. N) then
        write(*,*) "Value does not match at",val,int(Vout(val)) 
   end if
end do


deallocate(A)
if(err/=0) print'(a30,i9,i3)', 'ERROR in deallocation for A',err
deallocate(V)
if(err/=0) print'(a30,i9,i3)', 'ERROR in deallocation for V',err
deallocate(Vout)
if(err/=0) print'(a30,i9,i3)', 'ERROR in deallocation for Vout',err
call system_clock(tj,tk)

print'(a20,3x,f12.4)',"total time: ", dble(tj-ti)/dble(tk)

stop
end 

!-------------------------------------------------------
subroutine gemv(nval,alpha,A,V,Vout)

USE OMP_LIB
implicit none

integer:: row,col,A_row
integer:: nval,tid
real(8) :: alpha,sum_val
real(8),intent(in) :: A(1:nval*nval),V(1:nval)
real(8),intent(out):: Vout(1:nval)

!$omp parallel do default(shared) private(tid,row,col,A_row,sum_val)
do row=1,nval
   !tid=OMP_GET_THREAD_NUM()
   sum_val = 0.0
   A_row =(row-1)*nval
   !write(*,*) "total number of threads: ",tid,A_row,A_row+nval,nval*nval
   do col=1,nval
      sum_val = sum_val + A(A_row+col)*V(col)
   end do
   Vout(row) = sum_val * alpha
end do
!$omp end parallel do

end subroutine
