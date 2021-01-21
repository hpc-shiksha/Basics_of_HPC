#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int p(int j, int i, int number_nodes_x) {
int pos = (j-1) * number_nodes_x + i;
    return pos;
}

int main(int argc, char** argv) {

    //Define domain boundary and elements in x and y..
    const double DOMAIN_LENGTH_X = 1.;
    const double DOMAIN_LENGTH_Y = 1.;

    int NUMBER_STEPS_X;
    int NUMBER_STEPS_Y;
   
    scanf("%d%d", &NUMBER_STEPS_X, &NUMBER_STEPS_Y);

    double STEP_SIZE_X = DOMAIN_LENGTH_X / NUMBER_STEPS_X;
    double STEP_SIZE_Y = DOMAIN_LENGTH_Y / NUMBER_STEPS_Y;
 
    // also the coefficients..
    double COEFF_X = 1.0 / (STEP_SIZE_X * STEP_SIZE_X);
    double COEFF_Y = 1.0 / (STEP_SIZE_Y * STEP_SIZE_Y);

    int number_nodes_x, number_nodes_y;
    number_nodes_x = NUMBER_STEPS_X + 1;
    number_nodes_y = NUMBER_STEPS_Y + 1;

    // allocate matrices and vectors
    int i, j, k;
    int elements = number_nodes_x * number_nodes_y;
    
    double** A = (double** )malloc((elements+1) * sizeof(double* ));
    for (j = 0; j <= elements; j++) {
        A[j] = (double* )malloc((elements+1) * sizeof(double));
    }
   
    for (j = 1; j <= elements; j++) {
        for (i = 1; i <= elements; i++) {
            A[j][i] = 0.0;
        }
    }
    
    double* B = (double*)malloc((elements+1) * sizeof(double));
    double* X = (double*)malloc((elements+1) * sizeof(double));
    double* X_old = (double*)malloc((elements+1) * sizeof(double));


    for (j = 1; j <= elements; j++) {
        B[j] = 0.0;
        X[j] = 0.0;
        X_old[j] = 0.0;
    }

   
    // building local matrices
    for (j = 1; j <= number_nodes_y; j++) {     // leftmost boundary
        A[p(j, 1, number_nodes_x)][p(j, 1, number_nodes_x)] = 1.0;
        B[p(j, 1, number_nodes_x)] = 1.0;
    }
    
   
    for (j = 1; j <= number_nodes_y; j++) {     // rightmost boundary
        A[p(j, number_nodes_x, number_nodes_x)][p(j, number_nodes_x, number_nodes_x)] = 1.0;
        B[p(j, number_nodes_x, number_nodes_x)] = 0.0;
    }
     

    for (i = 1; i <= number_nodes_x; i++) {     // bottomost boundary
        A[p(1, i, number_nodes_x)][p(1, i, number_nodes_x)] = 1.0;
        B[p(1, i, number_nodes_x)] = 1.0;
    }
    
    for (i = 1; i <= number_nodes_x; i++) {     // topmost boundary
        A[p(number_nodes_y, i, number_nodes_x)][p(number_nodes_y, i, number_nodes_x)] = 1.0;
        B[p(number_nodes_y, i, number_nodes_x)] = 0.0;
    }

    for (j = 2; j <= number_nodes_y - 1; j++) {     // interior nodes
        for (i = 2; i <=number_nodes_x - 1; i++) {
            
            A[p(j, i, number_nodes_x)][p(j,i,number_nodes_x)] = -2 * (COEFF_X + COEFF_Y);
            A[p(j, i, number_nodes_x)][p(j-1, i, number_nodes_x)] = COEFF_Y;
            A[p(j, i, number_nodes_x)][p(j, i-1, number_nodes_x)] = COEFF_X;
            A[p(j, i, number_nodes_x)][p(j, i+1, number_nodes_x)] = COEFF_X;
            A[p(j, i, number_nodes_x)][p(j+1, i, number_nodes_x)] = COEFF_Y;
        }
    }

    // Data movement vectors for all processes..
    long long int NUMBER_ITERATION_MAX = 10000000000000; 
    double  row_error, local_error, global_error, global_error_max = 1e-12, sum;
   
    // local Matrix solver (jacobi)..
for (k = 1; k <= NUMBER_ITERATION_MAX; k++) {

    // Jacobi solver..
    global_error = 0.0;
    for (j = 1; j <= elements; j++) {
        sum = 0.0;

        for (i = 1; i <= elements; i++) {
            if (A[j][i] == 0)
                continue;
            if (j != i)
                sum = sum + A[j][i] * X_old[i];
        }

        X[j] = (B[j] - sum) / A[j][j];
        local_error = fabs(X[j] - X_old[j]);

        if (local_error > global_error)
            global_error = local_error;

        X_old[j] = X[j];
    }

    printf("Iteration #%d: \t Error: %e \n", k, global_error);
     
    if (global_error <= global_error_max)
        break;
}

    printf("Convergence attained\n");

}








