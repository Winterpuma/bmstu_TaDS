#include <stdio.h>
#include "output.h"
#include "matrices.h"

void print_matrix(const int *matr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%5d ", matr[i*m+j]);
        printf("\n");
    }
}

void print_array(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
}

void dbg_print(const int *matr, int n, int m, int *A, int *JA, int *AN, int *ANi, int n_z_el, int n_z_rows)
{
    printf("\nA: ");
    print_array(A, n_z_el);

    printf("\nJA: ");
    print_array(JA, n_z_el);

    printf("\nAN: ");
    print_array(AN, n_z_rows);

    printf("\nANi: ");
    print_array(ANi, n_z_rows);

    printf("\nmatrix:\n");
    print_matrix(matr, n, m);
}

