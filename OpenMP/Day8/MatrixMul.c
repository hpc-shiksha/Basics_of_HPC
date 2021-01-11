#include<stdio.h>
#include<stdlib.h>

double arr1[5120][5120],arr2[5120][5120],res[5120][5120];
int main(int argc, char *argv[]){
if(argc!=2){
printf(" Usage <executable-path> Seedvalue\n");
exit(0);
}
srand(atoi(argv[1]));
for(int i=0;i<5120;i++)
for(int j=0;j<5120;j++){
arr1[i][j]= i+j+rand()%1048576+0.5; arr2[i][j]= i+j+rand()
%1048576+0.5;
}
fprintf(stderr, "done");
int B=20;
//#pragma omp parallel for
for(int ii=0;ii<5120;ii+=B){//loop tiling
for(int kk=0;kk<5120;kk+=B){
for(int jj=0;jj<5120;jj+=B){
for(int i=ii;i<ii+B;i++){
for(int k=kk;k<kk+B;k++){ // loop interchange
for( int j=jj;j<jj+B;j+=2){//loop unrolling
res[i][j]+=arr1[i][k]*arr2[k][j];
res[i][j+1]+=arr1[i][k]*arr2[k][j];
}
}
}
}
}
}
}//end main
