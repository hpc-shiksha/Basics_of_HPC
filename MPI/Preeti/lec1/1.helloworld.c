 
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) 
{
  // initialize MPI
  MPI_Init (&argc, &argv);

  printf ("Hello, world!\n");

  // done with MPI
  MPI_Finalize();
}

