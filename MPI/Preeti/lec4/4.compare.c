// Timing codes

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
  int myrank, size;
  double dTime, maxTime;
  MPI_Status status;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  int count = atoi (argv[1]);
  int buf[count];

  // initialize data
  for (int i=0; i<count; i++)
      buf[i] = myrank + i*i;

  // Timing Bcast
  double sTime = MPI_Wtime();
  MPI_Bcast(buf, count, MPI_INT, 0, MPI_COMM_WORLD);
  double eTime = MPI_Wtime();
  dTime = eTime - sTime;

  MPI_Reduce (&dTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  if (!myrank) printf ("Broadcast time: %lf\n", maxTime);

  MPI_Barrier (MPI_COMM_WORLD);

  // Timing send receive
  sTime = MPI_Wtime();
  if (myrank == 0)
   for (int r=1; r<size; r++)
    MPI_Send (buf, count, MPI_INT, r, r, MPI_COMM_WORLD);
  else
   MPI_Recv (buf, count, MPI_INT, 0, myrank, MPI_COMM_WORLD, &status);
  eTime = MPI_Wtime();
  dTime = eTime - sTime;

  MPI_Reduce (&dTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  if (!myrank) printf ("Send/recv time: %lf\n", maxTime);

  MPI_Finalize();
  return 0;

}

