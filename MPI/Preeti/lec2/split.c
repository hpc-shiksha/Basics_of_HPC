
#include <stdio.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  
  int myrank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  int color = myrank%2;
  int newrank, newsize;

  MPI_Comm newcomm;
  MPI_Comm_split (MPI_COMM_WORLD, color, myrank, &newcomm);

  MPI_Comm_rank( newcomm, &newrank );
  MPI_Comm_size( newcomm, &newsize );

  printf("Rank %d new rank %d of %d\n", myrank, newrank, newsize);

  MPI_Comm_free(&newcomm);

  MPI_Finalize();
  return 0;
}
