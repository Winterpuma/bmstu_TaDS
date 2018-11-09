#ifndef MATRICES_H
#define MATRICES_H


void generate_matrix(int *matr, int n, int m, int fill);
void input_matrix(int *matr, int n, int m);
void count_non_zero(const int *matr, int n, int m, int *non_zero_rows, int *non_zero_elements);
void convert_matrix(const int *matr, int n, int m, int *A, int *JA, int *AN, int *ANi, int n_z_el, int n_z_rows);

#endif // MATRICES_H
