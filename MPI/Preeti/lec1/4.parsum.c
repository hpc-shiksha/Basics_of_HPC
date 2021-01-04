// Parallel sum of array
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
#define N 900000000

int main(int argc, char *argv[]) 
{
  int numtasks, rank, len, rc, i, sidx;
  double etime, stime, a[N], value, localsum;
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
 
  // random initialization
  srand(time(NULL));
  value = abs((numtasks-rank)*(20210401-rand()))%N;
  sidx = rank*N/numtasks;
  for (i=sidx; i<sidx+N/numtasks ; i++)
      a[i] = value; 

  // compute local sum
  localsum=0.0;
  stime = MPI_Wtime();
  for (i=sidx; i<sidx+N/numtasks ; i++)
      localsum += a[i]; 
      //localsum += sqrt(a[i]) + pow(a[i], 2.0); //compute-intensive 
  etime = MPI_Wtime();
  
  printf ("%d: Time to sum: %lf on %s\n", rank, etime - stime, hostname);

  // done with MPI
  MPI_Finalize();
}

