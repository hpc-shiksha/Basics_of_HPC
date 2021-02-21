%%cu



#include <stdio.h>
#include<iostream>
#include <cuda_runtime.h>

#define BLOCK_SIZE 1024
#define N 500000 //50000

using namespace std;


__global__ void sum( int *A,  int stride)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if (i % (2*stride) == 0)
    {
        A[i] = A[i] + A[i+stride];
    }
}

int main(void)
{
    
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float time;
    int threadsPerBlock;
    int blocksPerGrid; 
     int n,stride;

    threadsPerBlock = BLOCK_SIZE;
    n = N;
 
    blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;
    
    
    cudaError_t err = cudaSuccess;


    int *A = (int *)malloc(n * sizeof(int));
    int result=0;

    for (int i = 0; i < n; ++i)
    {
        A[i] = i+1;
        result = result + A[i];
    }
    
    int *dA = NULL;
    err = cudaMalloc((void **)&dA, n * sizeof(int));
   
    err = cudaMemcpy(dA, A, n * sizeof(int), cudaMemcpyHostToDevice);



    
    cudaEventRecord(start,0);
    for(stride=1; stride < n; stride = stride * 2)
    {     
      sum<<<blocksPerGrid, threadsPerBlock>>>(dA, stride);
    }

    cudaEventRecord(stop,0);
    cudaEventSynchronize (stop); 
    cudaEventElapsedTime (&time, start, stop); 
    
    cudaEventDestroy (start);
    cudaEventDestroy (stop);
 
     cout<<"Time taken: "<<time<<" milli seconds"<<endl;
    
    err = cudaMemcpy(A, dA, sizeof(int), cudaMemcpyDeviceToHost);   
    cudaDeviceSynchronize();
    cout<<A[0]<<endl;
    cout<<result<<endl;
    
    err = cudaFree(dA);    

    free(A);
    

    return 0;
}