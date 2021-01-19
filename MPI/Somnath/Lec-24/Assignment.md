## Assignment on point to point calls

Consider an MPI job to run in two processors (cores). A matrix, AMAT, of size 20x20 with (i,j)-th element as: (10*i+j)* (-1)^(myrank), where myrank is the rank of the processor,

1. Copy the last row of AMAT from Processor-0 to processor 1 using MPI Send and receive functions.

2. Now, copy the 5-th column of AMAT from Processor-1 to processor 0.
