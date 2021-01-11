#include <stdio.h>
#include <omp.h>

int main()
{
	int i,n=10;
	#pragma omp parallel shared(n) private(i)
	{
		#pragma omp for
			for(i=0;i<10;i++) {
	printf("Thread %d executes iteration %d\n",omp_get_thread_num(),i);
			}
	}
	printf("\n");
	return 0;
}
