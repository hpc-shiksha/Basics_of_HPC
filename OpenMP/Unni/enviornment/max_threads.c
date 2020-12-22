#include <stdio.h>
#include <omp.h>

int main( )
{
    omp_set_num_threads(8);
    printf("%d\n", omp_get_max_threads( ));
    #pragma omp parallel
        #pragma omp master
        {
            printf("%d\n", omp_get_max_threads( ));
        }

    printf("%d\n", omp_get_max_threads( ));

    #pragma omp parallel num_threads(3)
        #pragma omp master
        {
            printf("%d\n", omp_get_max_threads( ));
        }

    printf("%d\n", omp_get_max_threads( ));
}
