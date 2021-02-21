%%cu

#include<iostream>
#include<stdlib.h>
using namespace std;

#define BLOCK_SIZE 8
#define N 40

__device__ int dA[N][N];
int A[N][N];

void printMatrix(int n)
{
    int i,j;
 
  for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            cout<<A[i][j]<<" "; 
        }
          cout<<endl;
    }    
}
    
__global__ void transposeUsingSharedMemory(int n) 
{

    int r,c,newr,newc, lr, lc;

  __shared__ int sA[BLOCK_SIZE][BLOCK_SIZE];
 
    r = blockIdx.y * blockDim.y + threadIdx.y;
    c = blockIdx.x * blockDim.x + threadIdx.x; 
    lc = threadIdx.x; lr = threadIdx.y;
    newr = blockIdx.x * BLOCK_SIZE + threadIdx.y;
    newc = blockIdx.y * BLOCK_SIZE + threadIdx.x;

   
    sA[lc][lr]  = dA[r][c]; //dA[r * N + c];

    __syncthreads();

    //dA[newr * N + newc];
   dA[newr][newc] = sA[lr][lc];
        
}

int main()
{
    
    int n,i,j;
 
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float time;
 
     n = N;
    

    dim3 blockSize(BLOCK_SIZE,BLOCK_SIZE,1);
	  dim3 gridSize(N/BLOCK_SIZE,N/BLOCK_SIZE,1);
 
   
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            A[i][j] = i*10 + j;
        }
          cout<<endl;
    }    
    cudaMemcpyToSymbol(dA,A,sizeof(int)*N*N);
 
    cudaEventRecord(start,0);
    transposeUsingSharedMemory<<<gridSize,blockSize>>>(n);
    cudaEventRecord(stop,0);
    cudaEventSynchronize (stop); 
    cudaEventElapsedTime (&time, start, stop); 
    
    cudaEventDestroy (start);
    cudaEventDestroy (stop);
 
    cout<<"Time taken: "<<time<<" milli seconds"<<endl;
 
 
    cudaMemcpyFromSymbol(A,dA, sizeof(int)*N*N);
  
  printMatrix(n);


    

}