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

  // initialize array 
  srand(time(NULL));
  for (int i = 0; i < arrSize; i++) {
    message[i] = (double)rand() / (double)RAND_MAX;
  }

  double recvMessage[arrSize * numtasks]; //significant at the root process
  MPI_Gather(message, arrSize, MPI_DOUBLE, recvMessage, arrSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // finalize
  MPI_Finalize();

  return 0;
}
