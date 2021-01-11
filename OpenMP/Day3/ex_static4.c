#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i,n,t,chunk;
	double wtime;
	chunk=4;
	t=4;
	n=16;
	
	#pragma omp parallel for num_threads(t)
		for (i = 0; i < n; i++) {
	printf("Thread %d is doing iteration %d.\n", omp_get_thread_num( ), i);
		}
	
	printf("------------------------------\n");
	wtime = omp_get_wtime ( );	
	
	#pragma omp parallel for schedule(static,chunk) num_threads(t)
		for (i = 0; i < n; i++) {
			sleep(i); /* wait for i seconds */
	printf("Thread %d has completed iteration %d.\n",omp_get_thread_num(),i);
		}
	
	wtime = omp_get_wtime ( )-wtime;
	printf("Static Scheduling time needed- %f\n",wtime);
	printf("------------------------------\n");
	wtime = omp_get_wtime ( );
	
	#pragma omp parallel for schedule(dynamic) num_threads(t)
		for (i = 0; i < n; i++) {
			sleep(i); /* wait for i seconds */
	printf("Thread %d has completed iteration %d.\n", omp_get_thread_num( ), i);
		}
	
	wtime = omp_get_wtime ( )-wtime;
	printf("Dynamic Scheduling time needed- %f\n",wtime);

return 0;
}
