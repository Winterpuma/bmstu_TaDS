#ifndef OUTPUT_H
#define OUTPUT_H
#include "matrices.h"

void print_matrix(const int *matr, int n, int m);
void print_array(const int *arr, int len);
void print_list(struct IA *IA);
void print_advanced(const int *A, const int *JA, struct IA *IA, const int n_z_el);

#endif // OUTPUT_H
