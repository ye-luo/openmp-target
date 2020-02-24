program test_complex
    complex :: a, b, c
    a = cmplx(0, 1)
    b = cmplx(0.5, 0.3)
    !$omp target map(from, c)
    c = a*b
    !$omp end target
    if (abs(c - a*b) > 1e-7) then
      print *, "wrong value ", c, "right value ", a*b
    endif
end program test_complex
