 
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) 
{
  int numtasks, myrank, len;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  // initialize MPI
  MPI_Init (&argc, &argv);

  // get number of tasks
  MPI_Comm_size (MPI_COMM_WORLD, &numtasks);

  // need multiple of 4 processes for 2D virtual topology (just an example)
  if (numtasks%4 !=0) MPI_Abort(MPI_COMM_WORLD, 0);

  // get my rank
  MPI_Comm_rank (MPI_COMM_WORLD, &myrank);

  // get processor name 
  MPI_Get_processor_name (hostname, &len);

  if (0)
  printf ("Number of tasks=%d My rank=%d Running on %s\n", numtasks, myrank, hostname);

  // set up rows and columns in 2D virtual topology
  int rows = 4; 
  int cols = numtasks/rows;

  // create new group ranks array
  int ranks[cols], i, j=-1;
  for (i=(myrank/cols)*cols; i<((myrank/cols)+1)*cols; i++)
      ranks[++j] = i;

  // just to check
  if (0)
  for (i=0; i<cols; i++)
      printf ("%d: ranks[%d]=%d\n", myrank, i, ranks[i]);

  // get the world group
  MPI_Group g_group;
  MPI_Comm_group (MPI_COMM_WORLD, &g_group);

  // create new groups
  MPI_Group new_group;
  MPI_Group_incl (g_group, cols, ranks, &new_group);

  // create new communicators
  MPI_Comm new_comm;
  MPI_Comm_create_group (MPI_COMM_WORLD, new_group, myrank/cols, &new_comm);  //note the tag

  // size of new communicators
  int new_size, new_rank;
  MPI_Comm_size (new_comm, &new_size);
  MPI_Comm_rank (new_comm, &new_rank);
  printf ("Old rank %d, new rank %d\n", myrank, new_rank);

  // done with MPI
  MPI_Finalize();
}

