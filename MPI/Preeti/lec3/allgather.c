#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

  int rank, numtasks;

  // Setup
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  if (argc != 2) {
    printf("usage: %s number_of_doubles\n", argv[0]);
    return 1;
  }

  // Allocate message
  int arrSize = atoi(argv[1]);
  double message[arrSize];

  // Initialize array 
  for (int i = 0; i < arrSize; i++) {
    message[i] = i; 
  }

  // every process receives arrSize elements from other processes
  double recvMessage[arrSize * numtasks]; 
  MPI_Allgather(message, arrSize, MPI_DOUBLE, recvMessage, arrSize, MPI_DOUBLE, MPI_COMM_WORLD);

  // Verify 
  printf("%d: %lf\n", rank, recvMessage[arrSize-1]);

  // Finalize
  MPI_Finalize();

  return 0;
}
