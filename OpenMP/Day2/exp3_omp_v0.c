#include <stdio.h>
#include <omp.h>

int main()
{
	int ii;
	#pragma omp parallel 
	{
	for(ii=0;ii<10;ii++) {
		printf("Iteration: %d\n",ii);
	}
	}
	printf("\n");
	return 0;
}
