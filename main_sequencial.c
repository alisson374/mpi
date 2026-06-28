#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

int main()
{
    int inicio = 1;
    int fim = 2147483647;

    clock_t inicio_t = clock();

    int total = 0;

    for (int i = inicio; i <= fim; i++)
        if (ehPrimo(i))
            total++;

    clock_t fim_t = clock();

    double tempo = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;

    printf("=== Sequencial ===\n");
    printf("Primos: %d\n", total);
    printf("Tempo: %f s\n", tempo);

    return 0;
}