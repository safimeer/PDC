#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define ARRAY_SIZE 20

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator
    srand(time(NULL));

    // Generate random numbers on the root process
    int numbers[ARRAY_SIZE];
    if (rank == 0) {
        printf("Random numbers: ");
int i ;
        for (i = 0; i < ARRAY_SIZE; i++) {
            numbers[i] = rand() % 100;
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    // Divide the array among processes
    int local_array_size = ARRAY_SIZE / size;
    int local_numbers[local_array_size];
    MPI_Scatter(numbers, local_array_size, MPI_INT, local_numbers, local_array_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate local sum
    int local_sum = 0;
int i ;    
for (i = 0; i < local_array_size; i++) {
        local_sum += local_numbers[i];
    }

    // Gather local sums on root process
    int* all_sums = NULL;
    if (rank == 0) {
        all_sums = (int*)malloc(size * sizeof(int));
    }
    MPI_Gather(&local_sum, 1, MPI_INT, all_sums, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Print results on root process
    if (rank == 0) {
        int total_sum = 0;
        printf("Local sums: ");
int i ;        
for (i = 0; i < size; i++) {
            printf("%d ", all_sums[i]);
            total_sum += all_sums[i];
        }
        printf("\n");
        printf("Total sum: %d\n", total_sum);
        free(all_sums);
    }

    MPI_Finalize();
    return 0;
}
