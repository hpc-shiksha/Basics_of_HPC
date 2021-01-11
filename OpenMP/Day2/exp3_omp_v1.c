#include <stdio.h>
#include <omp.h>

int main()
{
	int ii;
	#pragma omp parallel private(ii)
	{
	for(ii=0;ii<10;ii++) {
		printf("Iteration: %d from %d\n",ii,omp_get_thread_num());
	}
	}
	printf("\n");
	return 0;
}
