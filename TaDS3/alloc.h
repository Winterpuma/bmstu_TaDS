#ifndef ALLOC_H
#define ALLOC_H

void allocate_matr(float **matr, float **A, int **JA, int n, int m);
void allocate_gen_matr(int **matr, int **A, int **JA, int n, int m, int *count, int fill);

#endif // ALLOC_H
