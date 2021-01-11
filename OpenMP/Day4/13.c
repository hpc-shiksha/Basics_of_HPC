#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int counter = 0;
	omp_set_num_threads(4);
	#pragma omp parallel
	{
			counter = 1;
		#pragma omp master
			sleep(9);
			
		#pragma omp barrier
			printf("%d\n", counter);
	}


        return 0;
}

