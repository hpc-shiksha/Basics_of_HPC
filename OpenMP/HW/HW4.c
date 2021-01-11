/* 
 * Write an OpenMP C code to compute 
 * the mean and standard deviation of a list of numbers. 
 * I/O will be performed by the Master serial.
 *
 */

#include <stdio.h>
#include <omp.h>
#include <math.h>
#define THREADS 4

int main(int argc,char *argv[])
{
	long int n,i;
	float list[1000],mean,stdev,sum=0.0,sum2=0.0;

	printf("Enter the size of the list: ");
	scanf("%ld",&n);
	printf("Enter the numbers in the list: ");
	for(i=0;i<n;i++)
		scanf("%f",&list[i]);
	omp_set_num_threads(THREADS);
	#pragma omp parallel 
	{
		#pragma omp for reduction(+:sum)
			for(i=0;i<n;i++) {
				sum=sum+list[i];	
		}
		#pragma omp master
			mean=sum/n;
		#pragma omp barrier
		#pragma omp for reduction(+:sum)
			for(i=0;i<n;i++) {
				sum2=sum2+(list[i]-mean)*(list[i]-mean);	
		}
		#pragma omp master
			stdev=sqrt(sum2/n);	
	}
	printf("Mean: %6.2f\nStandard Deviation: %6.4f\n",mean,stdev);

	return 0;
}
