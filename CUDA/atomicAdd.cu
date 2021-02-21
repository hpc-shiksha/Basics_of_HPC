%%cu
#include<stdio.h>
#define N 32

int A[N],count;
__device__ int dA[N], dCount;

void initHostArray()
{
    for(int i=0; i<N;i++)
    {
        A[i] = i;
    }
}
void printHostArray()
{
    for(int i=0; i<N;i++)
    {
        printf("%d \n",A[i]);
    }
}

__global__ void countEven()
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
 
    if(dA[i]%2==0)
    {
     atomicAdd(&dCount,1);
    }
}

int main()
{

 initHostArray();
 cudaMemcpyToSymbol(dA,A,sizeof(int)*N);
 countEven<<<1,N>>>();
 cudaMemcpyFromSymbol( &count, dCount, sizeof(int));
 cudaDeviceSynchronize();
 printf("%d ",count);
 return 0;

}
