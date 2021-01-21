### Case study: Domain Decomposition

1. Run the MPI Jacobi code for the following cases in 1, 2, 4, and 8 processes and check the speed-up:
    - nx= 10, ny= 10
    - nx= 40, ny= 40
    - nx=100, ny=100
    - nx=400, ny= 25

   Explain your observation.

2. Can you modify the existing code, so that instead of multiplying all element of row of A with guess vector x, it only does so for the non-zero elements?
