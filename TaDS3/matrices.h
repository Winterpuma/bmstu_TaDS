#ifndef MATRICES_H
#define MATRICES_H


void generate_matrix(int *matr, int n, int m, int fill);
void input_matrix(int *matr, int n, int m);

void count_non_zero(const int *matr, int n, int m, int *non_zero_rows, int *non_zero_elements);
void convert_matrix(const int *matr, int n, int m, int *A, int *JA, int *AN, int *ANi, int n_z_el, int n_z_rows);

void add_matrices_simple(const int *matr1, const int *matr2, int *matr3, int n, int m);
void add_matrices_advanced(const int *A1, const int *JA1, const int *AN1, const int *ANi1, int n_z_el1, int n_z_rows1,
                           const int *A2, const int *JA2, const int *AN2, const int *ANi2, int n_z_el2, int n_z_rows2,
                           int *A3, int *JA3, int *AN3, int *ANi3, int *n_z_el3, int *n_z_rows3);
void copy_row(const int *A1, const int *JA1, const int *AN1, const int *ANi1, int curr_i1, int max_i1, int max_iel,
              int *A3, int *JA3, int *AN3, int *ANi3, int *n_z_el3, int *n_z_rows3);
void add_rows(const int *A1, const int *JA1, const int *AN1, const int *ANi1, int curr_i1, int max_i1, int max_i1el,
              const int *A2, const int *JA2, const int *AN2, const int *ANi2, int curr_i2, int max_i2, int max_i2el,
              int *A3, int *JA3, int *AN3, int *ANi3, int *n_z_el3, int *n_z_rows3);

#endif // MATRICES_H
