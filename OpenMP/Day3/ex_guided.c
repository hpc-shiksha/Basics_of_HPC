#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#define THREADS 8
int main()
{
	int i,N=30;

	#pragma omp parallel for schedule(guided) num_threads(THREADS)
  	for (i = 0; i < N; i++) {
		sleep(i);	/* wait for i seconds */
    		printf("Thread %d has completed iteration %d.\n", omp_get_thread_num( ), i);
  	}

	return 0;
}
