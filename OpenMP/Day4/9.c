#include <stdio.h>
#include <omp.h>

int main()
{
	int i, j;
	i = 1;
	j = 2;
	omp_set_num_threads(16);
	#pragma omp parallel private(i) firstprivate(j)
	{
  		i = 3;
  		j = j + 2;
		#pragma omp master
			printf("%d %d\n", i, j);
	}
	printf("%d %d\n", i, j);

        return 0;
}

