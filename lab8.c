#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
    int rank, size;
    int value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    value = rank + 3;
    int accumulated_values[3] = {0};
    printf("Value %d from Rank %d\n",value,rank);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&value, &accumulated_values[0], 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &accumulated_values[1], 1, MPI_INT, MPI_PROD, 1, MPI_COMM_WORLD);
    MPI_Reduce(&value, &accumulated_values[2], 1, MPI_INT, MPI_MAX, 2, MPI_COMM_WORLD);
    if (rank == 0 || rank == 1 || rank == 2) {
        printf("Rank %d: Accumulated value: %d\n", rank, accumulated_values[rank]);}
    MPI_Finalize();
    return 0;}