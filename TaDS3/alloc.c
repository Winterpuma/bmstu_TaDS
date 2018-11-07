#include <stdio.h>
#include <strings.h>

void allocate_matr(int **matr, int **A int **JA, int n, int m)
{
    *matr = calloc(n*m, sizeof(int));
    *A = malloc(n*m * sizeof(int));
    *JA = malloc(n*m * sizeof(int));
}

void allocate_gen_matr(int **matr, int **A, int **JA, int n, int m, int *count, int fill)
{
    *matr = calloc(n*m, sizeof(int));
    generate_matrix(*matr, n, m, fill, count);
    *A = malloc(*count * sizeof(int));
    *JA = malloc(*count * sizeof(int));
}
