#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int ehPrimo(int n)
{
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i <= sqrt(n); i += 2)
        if (n % i == 0)
            return 0;

    return 1;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int inicio = 1;
    int fim = 2147483647;

    int intervalo = (fim - inicio + 1) / size;

    int meuInicio = inicio + rank * intervalo;
    int meuFim = (rank == size - 1)
                  ? fim
                  : meuInicio + intervalo - 1;

    double t0 = MPI_Wtime();

    int local = 0;

    for (int i = meuInicio; i <= meuFim; i++)
        if (ehPrimo(i))
            local++;

    int total = 0;

    if (rank == 0)
    {
        total = local;

        for (int i = 1; i < size; i++)
        {
            int recebido;
            MPI_Recv(&recebido, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += recebido;
        }

        double t1 = MPI_Wtime();

        printf("=== Paralelo ===\n");
        printf("Processos: %d\n", size);
        printf("Primos: %d\n", total);
        printf("Tempo: %f s\n", t1 - t0);
    }
    else
    {
        MPI_Send(&local, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}