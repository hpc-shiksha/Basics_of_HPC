#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

  int rank, numTasks;

  // Setup
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numTasks);

  if (argc != 2) {
    printf("usage: %s number_of_ints\n", argv[0]);
    return 1;
  }

  // Allocate message
  int arrSize = atoi(argv[1]);
  int message[arrSize * numTasks]; // every process sends to every other process

  // Initialize array 
  for (int i = 0; i < arrSize * numTasks; i++) {
    message[i] = i; 
  }

  // every process receives arrSize elements from other processes
  int recvMessage[arrSize * numTasks]; 
  MPI_Alltoall(message, arrSize, MPI_INT, recvMessage, arrSize, MPI_INT, MPI_COMM_WORLD);

  // Verify 
  for (int i = 0; i < arrSize * numTasks; i++) {
    printf("%d: %d\n", rank, recvMessage[i]);
  }

  // Finalize
  MPI_Finalize();

  return 0;
}
