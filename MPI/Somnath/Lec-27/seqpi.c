#include <stdio.h>
#include<time.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
      int ndarts=100000000;
      int nscore=0,nprocs,i,nscore_all;
      double x_coord,y_coord,pi,r;
      //srand(time(0));
      //throws dart at the board
      nscore=0;
      for(i=0;i<ndarts;i++)
      {
            //generate random numbers for x and y coordinates
            r=(double)rand()/(double)(RAND_MAX);
            x_coord=2.0*r-1.0;
            r=(double)rand()/(double)(RAND_MAX);
            y_coord=2.0*r-1.0;
            //if dart lands in circle increment score
            if((x_coord*x_coord) + (y_coord*y_coord) <1.)
            {
                  nscore+=1;
            }
      }
      //getpi
      pi=(4.0*nscore)/ndarts;
      printf("\ncalculated value pi is %1f after %d throws",ndarts,pi);
      printf("\nReal value of PI:3.1415926535897 \n");
      return 0;
}

                 
