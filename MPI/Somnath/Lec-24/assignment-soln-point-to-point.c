#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, numtasks;

    // Setup
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    // Check for two rank argument
    if (numtasks!=2) {
        printf("This is a two process program. exiting!\n");
        goto close;
    }

    int A[20][20];
    int i, j;

    // Populate the matrix
    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            A[i][j] = (10*i + j)* pow(-1, rank);
        }
    }

    // Creating buffer array for transfer
    int buffer[20];

    // Sending Last Row(20th) of A from process 0 to 1
    if (rank==0)
        MPI_Send(A+19, 20, MPI_INT, 1, 0, MPI_COMM_WORLD);

    else {
        for (i=0;i<20;i++) {
            buffer[i] = A[19][i];
        }

        MPI_Recv(A+19, 20, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // checking
        for (i=0;i<20;i++)
            if (buffer[i] != -A[19][i])
                printf("Some error in receving of Last Row from process 0 to 1\n");

        printf("Correct data received from process 0 to 1 (Row 20)\n");
    }

    // Sending 5th column of A from process 1 to 0
    // Since data is not contiguous (i.e column order) pack the data before sending
    if (rank==1) {
        for (i=0;i<20;i++) {
            buffer[i] = A[i][5];
        }

        MPI_Send(buffer, 20, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(buffer, 20, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // checking
        for (i=0;i<19;i++)
            if (buffer[i] != -A[i][5])
                printf("Some error in receving of 5th Col from process 0 to 1\n");

        // Unpack the data after receiving
        for (i=0;i<20;i++) {
            A[i][5] = buffer[i];
        }

        printf("Correct data received from process 1 to 0 (Col 5)\n");
    }

    // Finalize
close:
    MPI_Finalize();
}
