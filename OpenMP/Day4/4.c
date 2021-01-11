#include <stdio.h>
#include <omp.h>

int main()
{
       int x=0, size=16;
       omp_set_num_threads(size);
       #pragma omp parallel shared(x)
       {
        	    x=x+1;
        }
        printf("%d\n",x);
        return 0;
}

