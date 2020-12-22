#include<stdio.h>
#include<stdlib.h>
#include "generic.h"
#define size 10000
#define NT 8
int A[size][size];
int B[size][size];
int C[size][size];
int flag[size];//to set flag[i]==1 if arr[i] is maximum

int main(int argc, char *argv[]){
	srand(atoi(argv[1]));//Seed for random number command line integer value
	//generates random number
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			A[i][j]=rand()%1048576;
			B[i][j]=rand()%1048576;
        	 }
	}
	double t1=rtclock();
#pragma omp parallel for num_threads(8)
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
                 C[i][j]=A[i][j]+B[i][j];
double t2=rtclock();
	 printf("\nTIME =%f \n",(t2-t1)*1000);

}
/*Run  executable-path <integer-seed-value>
 *example:   ./a.out 3 */
