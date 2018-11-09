#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "matrices.h"


void allocate_matrices(int **matr1, int **matr2, int **matr3, int size)
{
    *matr1 = calloc(size, sizeof(int));
    *matr2 = calloc(size, sizeof(int));
    *matr3 = calloc(size, sizeof(int));
}

void allocate_two_arrays(int **a, int **b, int elements)
{
    *a = malloc(elements * sizeof(int));
    *b = malloc(elements * sizeof(int));
}

void free_all(int *matr, int *A, int *JA, int *AN, int *ANi)
{
    free(matr);
    free(A);
    free(JA);
    free(AN);
    free(ANi);
}
