#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[]) {
    int tid, n, div, temp=0, i;
    int array[40];
    srand(time(NULL));
    printf("Array\n");
    for (i = 0; i < 41; i++) {
        int randomNumber = (rand()%100)+1;
        array[i]=randomNumber;
        printf("%d\t",randomNumber);}
        printf("\n");
     #pragma omp parallel
    {n=omp_get_num_threads(); 
     div=40/n;
     tid=omp_get_thread_num();
     int x;
        printf("Processing in Thread = %d\n",tid);
        int localsum=0;
    for(x=tid*div;x<div*(tid+1);x++){
        printf("%d\t",array[x]);
        localsum+=array[x];
        }
        printf("\nLocal Sum = %d\n",localsum);
        }
 printf("Total no of thread is %d\n",n);
    return 0;   }