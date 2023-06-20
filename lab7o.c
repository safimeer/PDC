#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 10
#define NUM_PROCESSES 4

int main(int argc, char** argv) {
    int rank, size;
    int array[ARRAY_SIZE];
    int frequency[NUM_PROCESSES] = {0};
    int numbers_per_process, start_index, end_index;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Generate random numbers in the array on process 0
    if (rank == 0) {
printf("The Array: [");
int i;
        for (i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % NUM_PROCESSES;  // Generate numbers between 0 and NUM_PROCESSES-1
printf("%d ",array[i]);
        }printf("]\n");
    }

    // Broadcast the array to all processes
    MPI_Bcast(array, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Divide the array among processes
    numbers_per_process = ARRAY_SIZE / size;
    start_index = rank * numbers_per_process;
    end_index = (rank == size - 1) ? ARRAY_SIZE - 1 : start_index + numbers_per_process - 1;

    // Calculate frequency of numbers for each process
int i;
    for (i = start_index; i <= end_index; i++) {
        frequency[array[i]]++;
    }

    // Gather the frequencies from all processes
    int total_frequency[NUM_PROCESSES] = {0};
    MPI_Allreduce(frequency, total_frequency, NUM_PROCESSES, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Print the frequencies on each process
    for (i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d: Frequency of number %d is %d\n", rank, i, total_frequency[i]);
    }

    MPI_Finalize();

    return 0;
}
