// Timing codes

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

  double sTime = MPI_Wtime();
  MPI_Bcast(buf, count, MPI_INT, 0, MPI_COMM_WORLD);
  double eTime = MPI_Wtime();

  printf ("%lf\n", eTime - sTime);

  MPI_Finalize();
  return 0;

}

