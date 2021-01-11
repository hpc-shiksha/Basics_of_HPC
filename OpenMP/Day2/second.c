#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int id;
	double wtime;

	printf("Number of processors available: %d\n",omp_get_num_procs());
	printf("Number of threads: %d\n",omp_get_max_threads());
	wtime=omp_get_wtime();
	printf("Outside the parallel region\n");
	id=omp_get_thread_num();
	printf("Hello from process %d\nGoing inside the parallel region\n",id);
	#pragma omp parallel private(id) 
	{
		id=omp_get_thread_num();
		printf("Hello from process %d\n",id);
	}
	wtime=omp_get_wtime() - wtime;
	printf("Back from the parallel region. Normal execution\n");
	printf("Elapsed wall clock time %f\n",wtime);
	return 0;
}
