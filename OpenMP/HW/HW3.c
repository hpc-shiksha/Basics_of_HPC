/* 
 * Write a serial program to check if a given number is prime or not. 
 * Report the required time.
 *
 * Convert it to a OpenMP code.
 * Add best scheduling algorithm
 */

#include <stdio.h>
#include <omp.h>
#include <time.h>
#define THREADS 4

int main(int argc,char *argv[])
{
	clock_t start,stop;
	long int n,i,chunk;
	char flag='y';

	start=clock();
	sscanf(argv[1],"%ld",&n);
	chunk=n/THREADS;
#pragma omp parallel for schedule(static,chunk) num_threads(THREADS)
	for(i=2;i<n;i++) {
		if(n%i==0) flag='n';	
	}
	(flag=='n')? printf("%ld is not prime!\n",n):printf("%ld is prime!\n",n);
	stop=clock();
	printf("Time required in milliseconds: %ld\n",stop-start);

	return 0;
}
