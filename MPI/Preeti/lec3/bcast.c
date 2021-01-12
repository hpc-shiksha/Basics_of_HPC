
#include <stdio.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  int myrank, buf[100];
  int count = 10;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );

  // initialize data
  for (int i=0; i<count; i++)
      buf[i] = myrank + i*i;

  // bcast collective call - should be called by all processes of the communicator specified in the call
  MPI_Bcast(buf, count, MPI_INT, 0, MPI_COMM_WORLD);

  // verify
  for (int i=0; i<count; i++)
      printf ("%d: buf[%d]=%d\n", myrank, i, buf[i]);

  MPI_Finalize();
  return 0;

}

