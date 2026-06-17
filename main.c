#include <stdio.h>
#include <mpich/mpi.h>

int main()
{
  printf("mpi \n");

  MPI_Init();

  return 0;
}