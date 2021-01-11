#include <stdio.h>
#include <omp.h>

int main( )
{
    omp_set_num_threads(4);
    printf("%d\n", omp_in_parallel( ));

    #pragma omp parallel
        #pragma omp master
        {
            printf("%d\n", omp_in_parallel( ));
        }
}
