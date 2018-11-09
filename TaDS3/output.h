#ifndef OUTPUT_H
#define OUTPUT_H
#include "matrices.h"

void print_matrix(const int *matr, int n, int m);
void print_array(int *arr, int len);
void dbg_print(const int *matr, int n, int m, int *A, int *JA, int *AN, int *ANi, int n_z_el, int n_z_rows);

#endif // OUTPUT_H
