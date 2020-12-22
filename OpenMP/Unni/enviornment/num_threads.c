#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(4);
    printf("%d\n", omp_get_num_threads( ));
    #pragma omp parallel
        #pragma omp master
        {
            printf("%d\n", omp_get_num_threads( ));
        }

    printf("%d\n", omp_get_num_threads( ));

    #pragma omp parallel num_threads(3)
        #pragma omp master
        {
            printf("%d\n", omp_get_num_threads( ));
        }

    printf("%d\n", omp_get_num_threads( ));
}
