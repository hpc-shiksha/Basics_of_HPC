%%cu

#include<stdio.h>

__device__ int dA[4][10];
int A[4][10];

void initializeHostArray()
{
    for(int i=0; i<4; i++)
     {
      for(int j=0; j<10; j++)
      {
          A[i][j] = i * 10 + j;
      }
     }
}
void printHostArray()
{
    for(int i=0; i<4; i++)
     {
      for(int j=0; j<10; j++)
      {
          printf("%d ",A[i][j]);
      }
      printf("\n");
     }
}
__global__ void increment()
{
    int r,c;
    c = blockIdx.x * blockDim.x + threadIdx.x;
    r = blockIdx.y * blockDim.y + threadIdx.y;
    dA[r][c]++;
}
int main()
{

     dim3 threadsPerBlock(5,2);
     dim3 blocksPerGrid(2,2);

     initializeHostArray();
     printHostArray();
     cudaMemcpyToSymbol(dA, A, 40*sizeof(int));
     
     increment<<<blocksPerGrid, threadsPerBlock>>>();
     
     cudaMemcpyFromSymbol(A, dA, 40*sizeof(int));
     printHostArray();
     cudaDeviceSynchronize();
}