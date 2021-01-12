
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  int myrank, size, sendval[2], maxval[2];
  MPI_Status status;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  for (int i=0; i<2; i++)
    sendval[i] = myrank+i; 

  MPI_Allreduce(sendval, maxval, 2, MPI_INT, MPI_SUM, MPI_COMM_WORLD); // reduced value present in all processes  

  for (int i=0; i<2; i++)
    printf ("%d maxval[%d]=%d\n", myrank, i, maxval[i]);

  MPI_Finalize();
  return 0;

}

