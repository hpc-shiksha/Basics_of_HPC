#include "mpi.h"
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
      int ndarts=100000;
      int nscore=0,n,myid,nprocs,i,j,nscore_all;
      int ntot;
      double x_coord,y_coord,pi,pi_all;
      int ranks[1];
        
      MPI_Init(&argc,&argv);
      MPI_Status status;
      MPI_Group group_world,group_new;
      MPI_Comm new_comm;
      MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
      MPI_Comm_rank(MPI_COMM_WORLD,&myid);
      MPI_Comm_group(MPI_COMM_WORLD,&group_world);
      ranks[0]= nprocs-1;
      MPI_Group_excl(group_world,1,ranks,&group_new);
      MPI_Comm_create(MPI_COMM_WORLD,group_new,&new_comm);
      ntot=2*ndarts;
      double r[ntot];
      if(myid==nprocs-1)
      {
            for (i=1;i<nprocs-1;i++)
            {
                  for(j=0;j<ntot;j++)
                  {
                        r[j]=(double)rand()/(double)(RAND_MAX);
                  }
                  MPI_Send(&r,2*ndarts,MPI_DOUBLE,i-1,10,MPI_COMM_WORLD);
            }
      }
      if(myid< nprocs-1)
      {
            //throws dart at the board
            nscore=0;
            MPI_Recv(&r,2*ndarts,MPI_DOUBLE,nprocs-1,10,MPI_COMM_WORLD,&status);
            for(n=0;n<ndarts;n++)
            {
                  //generate random numbers for x and y coordinates
                  x_coord=(2.0*r[n])-1.0;
                  y_coord=(2.0*r[n+ndarts])-1.0;
                  //if dart lands in circle increment score
                  if((x_coord*x_coord + y_coord*y_coord) <1.)
                  {
                       nscore+=1;
                  }
            }
            //get pi
            pi=(4.0*nscore)/ndarts;
            //get sum pi
            MPI_Allreduce(&nscore,&nscore_all,1,MPI_INT,MPI_SUM,new_comm);
            printf("\n local pi %lf id %d total score %d local score %d\n", pi,myid,nscore_all,nscore);    
            if (myid==0)
            {
                  pi_all=4.0*nscore_all/(ndarts*(nprocs-1));
                  printf("\nafter %d throws , combined pi=%.16lf",ndarts*(nprocs-1),pi_all);
            }
      }
      if(myid==0)printf("\nReal value of PI:3.1415926535897\n");
      MPI_Finalize();
      return 0;
}

                 
