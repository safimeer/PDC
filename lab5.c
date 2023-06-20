#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int n = 10;
  int data[n];
  int i;
  srand(rank);
  for (i = 0; i < n; i++) {
    data[i] = rand() % 10;
  }

  int local_sum = 0;
  for (i = 0; i < n; i++) {
    local_sum += data[i];
  }

  printf("Rank %d local sum = %d\n", rank, local_sum);

  int global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("Global Sum = %d\n", global_sum);
  }

  MPI_Finalize();
  return 0;
}
