
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  int myrank, size, sendval, maxval;
  MPI_Status status;

  struct {
   float val;
   int rank;
  } buf, recvbuf;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  // reduction of 1 integer
  sendval = myrank; // initialization
  MPI_Reduce(&sendval, &maxval, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // find max of sendvals
  //printf ("%d reduce integer %d\n", myrank, maxval);

  // location of rank with MAX value
  buf.val = myrank * 2.0;
  buf.rank = myrank * 2.0;
  MPI_Reduce(&buf, &recvbuf, 1, MPI_FLOAT_INT, MPI_MAXLOC, size-1, MPI_COMM_WORLD);
  printf ("%d max val=%f %d\n", myrank, recvbuf.val, recvbuf.rank);

  MPI_Finalize();
  return 0;

}

