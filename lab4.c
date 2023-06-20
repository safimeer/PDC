#include <stdio.h>
#include <mpi.h>
int main(int argc,char **argv){
int i=0, p,rank,a[50],b[25],c[25];
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&p);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
if(rank==0){
MPI_Scatter(&a,25,MPI_INT,&b,25,MPI_INT,0,MPI_COMM_WORLD);
for(i;i<25;i++){

int flag = 1;
int x = 2;  
    // loop to iterate through 2 to N/2
    for(x = 2; x <= b[i] / 2; x++){
  
        // if N is perfectly divisible by i
        // flag is set to 0 i.e false
        if (b[i] % x == 0) {
            flag = 0;
            break;
        }}

if(flag){
printf("proca : %d is prime \n",b[i]);
}
else
{
printf("procb : %d is non-prime \n",b[i]);
}}}
else{
MPI_Scatter(&a,25,MPI_INT,&c,25,MPI_INT,0,MPI_COMM_WORLD);
for(i;i<25;i++){

int flag = 1;
int x = 2;  
    // loop to iterate through 2 to N/2
    for(x = 2; x <= c[i] / 2; x++){
  
        // if N is perfectly divisible by i
        // flag is set to 0 i.e false
        if (c[i] % x == 0) {
            flag = 0;
            break;
        }}

if(flag){
printf("proc1 : %d is prime \n",c[i]);
}
else
{
printf("proc1 : %d is non-prime \n",c[i]);
}}}
MPI_Finalize();
}
