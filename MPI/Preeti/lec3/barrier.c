 
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) 
{
  int numtasks, rank, len;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  // initialize MPI
  MPI_Init (&argc, &argv);

  // get number of tasks
  MPI_Comm_size (MPI_COMM_WORLD, &numtasks);

  // get my rank
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  // this one is obvious
  MPI_Get_processor_name (hostname, &len);

  // even processes print
  if (rank % 2 == 0) printf ("Number of tasks=%d My rank=%d Running on %s\n", numtasks, rank, hostname);

  // barrier
  MPI_Barrier (MPI_COMM_WORLD);		// all processes should enter this call

  // odd processes print
  if (rank % 2 != 0) printf ("Number of tasks=%d My rank=%d Running on %s\n", numtasks, rank, hostname);

  // done with MPI
  MPI_Finalize();
}

