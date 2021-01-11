#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i,j,n,m,temp,a[100][100];
	n=m=7;
	#pragma omp parallel private(temp,j)
	{
	for(i=0;i<=n*m-1;i++) {
		temp=i/m+1;
		j=i%m+1;
		sleep(1);
		a[temp][j]=temp+100*(j-1);
	}
	}
	for(i=0;i<=n*m-1;i++) {
		temp=i/m+1;
		j=i%m+1;
		if(i%m==0) printf("\n");
		printf("%d\t",a[temp][j]);
	}
	printf("\n");
	return 0;
}
