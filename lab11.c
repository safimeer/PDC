#include<stdio.h>
#include<omp.h>

int factorial(int y) {
    return (y == 0 || y == 1) ? 1 : y * factorial(y - 1);
}

int main(int argc, char **argv) {
    float T, ans = 0, x = 3;
    int tid;

    #pragma omp parallel private(tid, T)
    {
        tid = omp_get_thread_num();

        if (tid == 0) {
            T = (x) / factorial(1);
        } else if (tid == 1) {
            T = (x * x) / factorial(2);
        } else if (tid == 2) {
            T = (x * x * x) / factorial(3);
        } else if (tid == 3) {
            T = (x * x * x * x) / factorial(4);
        }

        printf("Term calculated in Thread %d: %f\n", tid, T);

        #pragma omp critical
        {
            ans = ans + T;
        }
    }

    printf("Taylor series answer: %f\n", 1 + ans);

    return 0;
}
