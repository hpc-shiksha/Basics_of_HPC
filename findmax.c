#include<stdio.h>
#include<stdlib.h>
#include "generic.h"
#define size 10000
#define NT 8
int arr[size];
int flag[size];//to set flag[i]==1 if arr[i] is maximum

int main(int argc, char *argv[]){
	srand(atoi(argv[1]));//Seed for random number command line integer value
	//generates random number
	for(int i=0;i<size;i++)arr[i]=rand()%1048576;
	//initialize flag[i]=1 for 0<=i<=size
	for(int i=0;i<size;i++) flag[i]=1;
	double t1=rtclock();
#pragma omp parallel for num_threads(NT)
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		//if arr[i] is not maximum set flag[i]=0
		    if(arr[i]<arr[j])flag[i]=0;
	double t2=rtclock();
	 printf("\nTIME =%f \n",(t2-t1)*1000);

        //print maximum element arr[i] for which flag[i] still 1.
	for(int i=0;i<size;i++)if(flag[i]==1)printf("arr[%d]= %d\n",i,arr[i]);
}
/*Run  executable-path <integer-seed-value>
 *example:   ./a.out 3 */
