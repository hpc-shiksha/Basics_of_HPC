#include <stdio.h>
#include <omp.h>
int main()
{
        int x=0, size=12;
        omp_set_num_threads(size);
        #pragma omp parallel shared(x)
        {
               #pragma omp critical
               {
               	 x=x+1;
               }
        }
        printf("%d\n",x);
        return 0;
}
