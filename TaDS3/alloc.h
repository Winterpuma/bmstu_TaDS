#ifndef ALLOC_H
#define ALLOC_H

int allocate_matrices(int **matr1, int **matr2, int **matr3, int size);
void allocate_two_arrays(int **a, int **b, int elements);

void free_all(int *matr, int *A, int *JA, int *AN, int *ANi);

#endif // ALLOC_H
