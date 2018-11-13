#ifndef TADS_TRY_ALLOC_H
#define TADS_TRY_ALLOC_H
#include "matrices.h"

int allocate_matrices(int **matr1, int **matr2, int **matr3, int size);
void allocate_two_arrays(int **a, int **b, int elements);

void free_all(int *matr, int *A, int *JA, struct IA *IA);

#endif //TADS_TRY_ALLOC_H
