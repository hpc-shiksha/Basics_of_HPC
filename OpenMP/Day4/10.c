#include <stdio.h>
#include <omp.h>

int main()
{
	int i, a[10],b[10],n=10;
	omp_set_num_threads(16);
	i=-1;
	#pragma omp parallel 
	{ 
		#pragma omp for lastprivate(i) 
//		#pragma omp for private(i) 
			for (i=0; i<n-1; i++) 
				a[i] = b[i] + b[i+1];
	} 
	printf("i=%d\n",i);
	a[i]=b[i];

        return 0;
}

