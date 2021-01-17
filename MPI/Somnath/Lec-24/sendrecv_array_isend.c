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

  int count = 10000;
  int num[count];
  int num1[count];

  if (world_rank == 0) {
    for (int i=0; i<count; i++) {
        num[i] = i;
    }
  }
  else if (world_rank == 1) {
    for (int i=0; i<count; i++) {
        num[i] = count - i -1;
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Request request = MPI_REQUEST_NULL;
  MPI_Status status;

  if (world_rank == 0) {
    
    MPI_Isend(num, count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);

    MPI_Irecv(num1, count, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);

  } else if (world_rank == 1) {

    MPI_Isend(num, count, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);

    MPI_Irecv(num1, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

  }

  MPI_Wait(&request, &status);

  MPI_Barrier(MPI_COMM_WORLD);

  if (world_rank == 0) {
    int data_correct;
    for (int i=0; i<count; i++) {
        if (num1[i] == count -i -1)
            data_correct = 1;
        else {
            data_correct = 0;
            break;
        }
    }
    printf("Process 0 received correct data from process 1?: %d\n", data_correct);
  }
  else if (world_rank == 1) {
    int data_correct;
    for (int i=0; i<count; i++) {
        if (num1[i] == i)
            data_correct = 1;
        else {
            data_correct = 0;
            break;
        }
    }
    printf("Process 1 received correct data from process 0?: %d\n", data_correct);
  }

  MPI_Finalize();
}
