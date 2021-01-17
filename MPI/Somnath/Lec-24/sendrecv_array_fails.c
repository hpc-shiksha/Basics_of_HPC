#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv) {
  MPI_Status  status;
  MPI_Init(&argc, &argv);
  int size,rank, count=10000;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int num[count], num1[count];
  if (rank == 0) {
    for (int i=0; i<count; i++) {
        num[i] = i;
  }}
  else if (ank == 1) {
    for (int i=0; i<count; i++) {
        num[i] = count - i -1;
  }}
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
    MPI_Send(num, count, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Recv(num1, count, MPI_INT, 1, 1, MPI_COMM_WORLD, &Status);
  } else if (world_rank == 1) {
    MPI_Recv(num1, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status);
    MPI_Send(num, count, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }
  if (rank == 0) {
	  printf("Process 0 received data from process 1\n");
  }else{
	  printf("Process 1 received data from process 0\n");
  }
  MPI_Finalize();
}
