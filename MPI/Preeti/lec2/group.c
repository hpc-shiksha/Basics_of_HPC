 
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

//  printf ("Number of tasks=%d My rank=%d Running on %s\n", numtasks, rank, hostname);

  // get the world group
  MPI_Group g_group;
  MPI_Comm_group (MPI_COMM_WORLD, &g_group);

  // create new group ranks array
  int ranks[numtasks/2+1], i, j=-1;
  for (i=0; i<numtasks; i++)
      if (i%2 == 0) ranks[++j] = i ;
  int ranks_size = j+1;

  // just to check
  if (!rank && 0)
  for (i=0; i<ranks_size; i++)
      printf ("ranks[%d]=%d\n", i, ranks[i]);

  // create a new group
  MPI_Group new_group;
  MPI_Group_incl (g_group, ranks_size, ranks, &new_group);

  MPI_Comm new_comm;
  MPI_Comm_create_group (MPI_COMM_WORLD, new_group, 123, &new_comm);

  // size of new comm
  int new_size, new_rank;
  if (rank%2==0) { 
     MPI_Comm_size (new_comm, &new_size);
     MPI_Comm_rank (new_comm, &new_rank);
     if (!rank && 0) printf("New size is %d, Length of ranks is %d\n", new_size, ranks_size);
     printf ("Old rank %d, new rank %d\n", rank, new_rank);
  }

  // done with MPI
  MPI_Finalize();
}

