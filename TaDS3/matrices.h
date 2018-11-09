#ifndef MATRICES_H
#define MATRICES_H

struct IA
{
    int i;
    int Nk;
    struct IA *next;
};

void generate_matrix(int **matr, int n, int m, int fill);
void input_matrix(int **matr, int n, int m);
void count_non_zero(const int *matr, int n, int m, int *non_zero_rows, int *non_zero_elements);
void convert_matrix(int *matr, int n, int m, int **A, int **JA, struct IA *IA, int non_zero_rows, int non_zero_elements);

#endif // MATRICES_H
