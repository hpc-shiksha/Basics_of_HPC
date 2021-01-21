#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int p(int j, int i, int number_nodes_x) {
int pos = (j-1) * number_nodes_x + i;
    return pos;
}

int main(int argc, char** argv) {

    //MPI calls..
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //Define domain boundary and elements in x and y..
    const double DOMAIN_LENGTH_X = 1.;
    const double DOMAIN_LENGTH_Y = 1.;

    int NUMBER_STEPS_X;
    int NUMBER_STEPS_Y;
   
    //Read no. of elements in x and y by the master process..
    if (world_rank == 0) {
        scanf("%d%d", &NUMBER_STEPS_X, &NUMBER_STEPS_Y);
        //printf("Steps in X and Y: %d %d\n", NUMBER_STEPS_X, NUMBER_STEPS_Y);
    }

    //Inform the rest of the processes..
    MPI_Bcast(&NUMBER_STEPS_X, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&NUMBER_STEPS_Y, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
  
    //Calculate the step size in x and y dir in all of the processes..
    double STEP_SIZE_X = DOMAIN_LENGTH_X / NUMBER_STEPS_X;
    double STEP_SIZE_Y = DOMAIN_LENGTH_Y / NUMBER_STEPS_Y;
 
    // also the coefficients..
    double COEFF_X = 1.0 / (STEP_SIZE_X * STEP_SIZE_X);
    double COEFF_Y = 1.0 / (STEP_SIZE_Y * STEP_SIZE_Y);

    int number_steps_process_x;
    
    // load balancing in terms of steps in X (domain partitioning)..
    number_steps_process_x = (NUMBER_STEPS_X / world_size);

    if (world_rank < NUMBER_STEPS_X % world_size) {
        number_steps_process_x++;
    }
    
    // local numbering of nodes..
    int number_nodes_x, number_nodes_y;
    number_nodes_x = number_steps_process_x + 1;
    number_nodes_y = NUMBER_STEPS_Y + 1;

    // incorporate domain overlap between processes..
    if (world_rank == 0 || world_rank == world_size - 1) {
        number_nodes_x++;
    }
    else {
        number_nodes_x += 2;
    }
    
    // global start and end node in a process in x dir..
    int node_x_start, node_x_end;
    if (world_rank < NUMBER_STEPS_X % world_size) {
        node_x_start = (world_rank * number_steps_process_x) + 1;
        node_x_end = (world_rank + 1) * number_steps_process_x  ;
    }
    else {
        node_x_start = (NUMBER_STEPS_X % world_size) * (number_steps_process_x + 1) +
                           (world_rank - (NUMBER_STEPS_X % world_size)) * 
                           number_steps_process_x + 1;
        node_x_end = (NUMBER_STEPS_X % world_size) * (number_steps_process_x + 1) + 
                           ((world_rank + 1) - (NUMBER_STEPS_X % world_size)) *
                           number_steps_process_x;
    }
    
    if (world_rank == world_size - 1) {
        node_x_end++;
    }

    // allocate local matrices and vectors
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
    if (world_rank == 0) {
        for (j = 1; j <= number_nodes_y; j++) {     // leftmost boundary
            A[p(j, 1, number_nodes_x)][p(j, 1, number_nodes_x)] = 1.0;
            B[p(j, 1, number_nodes_x)] = 1.0;

            A[p(j, number_nodes_x, number_nodes_x)][p(j, number_nodes_x, number_nodes_x)] = 1.0;
            B[p(j, number_nodes_x, number_nodes_x)] = 0.0;
        }
    }
   
    if (world_rank == world_size - 1) {
        for (j = 1; j <= number_nodes_y; j++) {     // rightmost boundary
            A[p(j, number_nodes_x, number_nodes_x)][p(j, number_nodes_x, number_nodes_x)] = 1.0;
            B[p(j, number_nodes_x, number_nodes_x)] = 0.0;
            
            A[p(j, 1, number_nodes_x)][p(j, 1, number_nodes_x)] = 1.0;
            B[p(j, 1, number_nodes_x)] = 0.0;
        }
    }

    for (i = 1; i <= number_nodes_x; i++) {     // bottomost boundary
        A[p(1, i, number_nodes_x)][p(1, i, number_nodes_x)] = 1.0;
        B[p(1, i, number_nodes_x)] = 1.0;
    }
    
    for (i = 1; i <= number_nodes_x; i++) {     // topmost boundary
        A[p(number_nodes_y, i, number_nodes_x)][p(number_nodes_y, i, number_nodes_x)] = 1.0;
        B[p(number_nodes_y, i, number_nodes_x)] = 0.0;
    }

    if (world_rank != 0 && world_rank != world_size - 1) {    // x boundaries for all innermost processes
        for (j = 2; j <= number_nodes_y - 1; j++) {
            A[p(j, 1, number_nodes_x)][p(j, 1, number_nodes_x)] = 1.0;
            B[p(j, 1, number_nodes_x)] = 0.0;
            
            A[p(j, number_nodes_x, number_nodes_x)][p(j, number_nodes_x, number_nodes_x)] = 1.0;
            B[p(j, number_nodes_x, number_nodes_x)] = 0.0;
        }
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
    double* Send_to_R = (double*)malloc((elements+1) * sizeof(double));
    double* Send_to_L = (double*)malloc((elements+1) * sizeof(double));
    double* Receive_from_L = (double*)malloc((elements+1) * sizeof(double));
    double* Receive_from_R = (double*)malloc((elements+1) * sizeof(double));
    double  row_error, local_error, global_error, global_error_max = 1e-12, sum;
   
    // local Matrix solver (jacobi)..
for (k = 1; k <= NUMBER_ITERATION_MAX; k++) {


        // populate send left / right buffers..
        if (world_rank != world_size - 1) {
            for (j = 1; j <= number_nodes_y; j++) {
                Send_to_R[j] = X_old[p(j, number_nodes_x - 2, number_nodes_x)];
            }
        }
        if (world_rank != 0) {
            for (j = 1; j <= number_nodes_y; j++) {
                Send_to_L[j] = X_old[p(j, 3, number_nodes_x)];
            }
        }
        

    
    // Data transfer between processes..
    if (world_rank % 2 == 0) {      // Even processes sending data to their Right
        if (world_rank != world_size - 1) 
            MPI_Send(Send_to_R, number_nodes_y, MPI_DOUBLE, world_rank + 1, 100,
                                                       MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(Receive_from_L, number_nodes_y, MPI_DOUBLE, world_rank - 1, 100,
                                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    if (world_rank % 2 == 1) {      // Odd processes sending data to their Right
        if (world_rank != world_size - 1) 
            MPI_Send(Send_to_R, number_nodes_y, MPI_DOUBLE, world_rank + 1, 200,
                                                        MPI_COMM_WORLD);
    }
    else {
        if (world_rank != 0)
        MPI_Recv(Receive_from_L, number_nodes_y, MPI_DOUBLE, world_rank - 1, 200, 
                                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }


    if (world_rank % 2 == 0) {      // Even processes sending data to their Left
        if (world_rank != 0) 
            MPI_Send(Send_to_L, number_nodes_y, MPI_DOUBLE, world_rank - 1, 300,
                                                        MPI_COMM_WORLD);
    }
    else {
        if (world_rank != world_size - 1)
        MPI_Recv(Receive_from_R, number_nodes_y, MPI_DOUBLE, world_rank + 1, 300,
                                    MPI_COMM_WORLD,  MPI_STATUS_IGNORE);
    }


    if (world_rank % 2 == 1) {      // Odd processes sending data to their Left
            MPI_Send(Send_to_L, number_nodes_y, MPI_DOUBLE, world_rank - 1, 400,
                                                        MPI_COMM_WORLD);
    }
    else {
        if (world_rank != world_size - 1)
        MPI_Recv(Receive_from_R, number_nodes_y, MPI_DOUBLE, world_rank + 1, 400,
                                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    // Setting received buffers to appropriate locations..
    if (world_rank != 0 && world_rank != world_size - 1) {
        for (j = 2; j <= number_nodes_y - 1; j++) {
            B[p(j, 1, number_nodes_x)] = Receive_from_L[j];
            B[p(j, number_nodes_x, number_nodes_x)] = Receive_from_R[j];
        }
    }

    if (world_rank == 0) {
        for (j = 2; j <= number_nodes_y - 1; j++) {
            B[p(j, number_nodes_x, number_nodes_x)] = Receive_from_R[j];
        }
    }
    
    if (world_rank == world_size - 1) {
        for (j = 2; j <= number_nodes_y - 1; j++) {
            B[p(j, 1, number_nodes_x)] = Receive_from_L[j];
        }
    }

    // Jacobi solver for each process..
    local_error = 0.0;
    for (j = 1; j <= elements; j++) {
        sum = 0.0;

        for (i = 1; i <= elements; i++) {
            if (A[j][i] == 0)
                continue;
            if (j != i)
                sum = sum + A[j][i] * X_old[i];
        }

        X[j] = (B[j] - sum) / A[j][j];
        row_error = fabs(X[j] - X_old[j]);

        if (row_error > local_error)
            local_error = row_error;

        X_old[j] = X[j];
    }

    // calculate global error..
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(&local_error, &global_error, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Iteration #%d: \t Error: %e \n", k, global_error);
    }
   
    // stop if the global error is less than a set max
    if (global_error <= global_error_max)
        break;
}

    if (world_rank == 0) 
        printf("Convergence attained\n");

    MPI_Finalize();
}








