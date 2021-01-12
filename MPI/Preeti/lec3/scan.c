
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  int myrank, size, sendval, val;
  MPI_Status status;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  sendval = myrank; // initialization
  MPI_Scan (&sendval, &val, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD); // bit-wise OR 

  // verify - print from all ranks
  printf ("%d val=%d\n", myrank, val); 

  MPI_Finalize();
  return 0;

}

