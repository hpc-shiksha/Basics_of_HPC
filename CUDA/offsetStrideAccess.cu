%%cu
#include <stdio.h>
#define N 1024*1024 
#define BS 1024;
//1M elements 

__global__ void offsetAccess(int *A, int s)
{
  int i = blockDim.x * blockIdx.x + threadIdx.x + s;
  A[i] = A[i] + 1;
}

__global__ void strideAccess(int *A, int s)
{
  int i = (blockDim.x * blockIdx.x + threadIdx.x) * s;
  A[i] = A[i] + 1;
}

void offsetExperiment()
{
  int blockSize,  *dA, n;
  float time;;
  cudaEvent_t startEvent, stopEvent;
    
  n = N;  blockSize= BS;


  cudaMalloc(&dA, n * 32 * sizeof(int));
  cudaEventCreate(&startEvent);
  cudaEventCreate(&stopEvent);
  printf("#Bytes Requested = %d\n", n *4);
  printf("Offset -  Running time (ms)\n");
  
  for (int i = 1; i <= 32; i++) 
  {

    cudaEventRecord(startEvent,0);
    offsetAccess<<<n/blockSize, blockSize>>>(dA, i);
    cudaEventRecord(stopEvent,0);
    cudaEventSynchronize(stopEvent);

    cudaEventElapsedTime(&time, startEvent, stopEvent);
  
    printf(" %d %f  \n", i, time);

  }
  cudaEventDestroy(startEvent);
  cudaEventDestroy(stopEvent);
  cudaFree(dA);
}

void strideExperiment()
{
  int blockSize,  *dA, n;
  float time;;
  cudaEvent_t startEvent, stopEvent;
    
  n = N;  blockSize= BS;


  cudaMalloc(&dA, n * 32 * sizeof(int));
  cudaEventCreate(&startEvent);
  cudaEventCreate(&stopEvent);

  printf("#Bytes Requested = %d\n", n *4);

  printf("Stride - Running time (ms)\n");

  
  for (int i = 1; i <= 32; i++) 
  {
    cudaEventRecord(startEvent,0);
   
    strideAccess<<<n/blockSize, blockSize>>>(dA, i);
   
    cudaEventRecord(stopEvent,0);
    cudaEventSynchronize(stopEvent);
    cudaEventElapsedTime(&time, startEvent, stopEvent);
    printf(" %d  %f\n", i, time);

  }

  cudaEventDestroy(startEvent);
  cudaEventDestroy(stopEvent);
  cudaFree(dA);
}

int main(int argc, char **argv)
{

  offsetExperiment();
  strideExperiment();

  
}