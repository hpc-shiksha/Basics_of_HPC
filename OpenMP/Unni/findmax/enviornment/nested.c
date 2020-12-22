#include <stdio.h>
#include <omp.h>

int main( )
{
    omp_set_nested(1);
    omp_set_num_threads(4);
    printf("%d\n", omp_get_nested( ));
    #pragma omp parallel
        #pragma omp master
        {
            printf("%d\n", omp_get_nested( ));
        }
}
