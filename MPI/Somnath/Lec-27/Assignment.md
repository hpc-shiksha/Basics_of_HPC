### Case-study: Monte-Carlo Pi Simulation

Consider the Monte-Carlo Pi simulation MPI programs shown in class and also in the folder.

1. MPI_Send and MPI_Recv introduce latency in this latency. Explain.
2. Replace MPI_Send and MPI_Recv by non-blocking calls? How are the results with these changes? Why is it so? How can you use non-blocking calls in this program?

## Solution:
mcpic_isend.c is the solution to the assignment. Please run with MPI_Irecv with(out) MPI_Wait call respectively.
