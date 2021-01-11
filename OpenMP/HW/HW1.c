/* 
 * Write a serial program to check if a given number is prime or not. 
 * Report the required time.
 *
 */

#include <stdio.h>
#include <time.h>

int main(int argc,char *argv[])
{
	clock_t start,stop;
	long int n,i;
	char flag='y';

	start=clock();
	sscanf(argv[1],"%ld",&n);
	for(i=2;i<n;i++) {
		if(n%i==0) flag='n';	
	}
	(flag=='n')? printf("%ld is not prime!\n",n):printf("%ld is prime!\n",n);

	stop=clock();
	printf("Time required in milliseconds: %ld\n",stop-start);

	return 0;
}
