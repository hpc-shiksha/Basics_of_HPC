#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  MPI_Init(NULL, NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (world_size != 2) {
    printf("World size must be equal to 2");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  double number;
  if (world_rank == 0) {
    number = -1.123;

    MPI_Send(&number, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);

  } else if (world_rank == 1) {

    MPI_Recv(&number, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  }
  MPI_Finalize();
}
