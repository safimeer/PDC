#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[]) {
    int tid, nthread;
    #pragma omp parallel
    {tid=omp_get_thread_num();
        printf("Salam from TID = %d\n",tid);
     nthread=omp_get_num_threads();        }
    printf("Total no of thread is %d\n",nthread);
    return 0;}