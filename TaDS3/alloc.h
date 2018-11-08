#ifndef ALLOC_H
#define ALLOC_H

void allocate_matrix(int **matr, int **A, int **JA, int n, int m);
void allocate_gen_matrix(int **matr, int **A, int **JA, int n, int m, int fill);

struct IA* create(int i, int num);
struct IA* add(struct IA *node, int i, int num);
void free_all(struct IA *head);

#endif // ALLOC_H
