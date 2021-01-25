
#include <stdio.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  
  int myrank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

 
  int rows = 2; 
  int cols = size/rows;
  int color = myrank/cols;

  int newrank, newsize;
  MPI_Comm newcomm;
  MPI_Comm_split (MPI_COMM_WORLD, color, myrank, &newcomm);

  MPI_Comm_rank( newcomm, &newrank );
  MPI_Comm_size( newcomm, &newsize );

  printf("Old Rank %d new rank %d of size %d  of color %d\n", myrank, newrank, newsize, color);

  MPI_Comm_free(&newcomm);

  MPI_Finalize();
  return 0;
}


