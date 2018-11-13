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

void print_array(const int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
}

void print_list(struct IA *IA)
{
    struct IA *tmp = IA;

    printf("\nANi: ");
    if (tmp)
        for (; tmp != NULL; tmp = tmp->next)
            printf("%d ", tmp->i, &tmp);


    tmp = IA;
    printf("\nAN: ");
    if (tmp)
        for (; tmp != NULL; tmp = tmp->next)
            printf("%d ", tmp->Nk, &tmp);
}

void print_advanced(const int *A, const int *JA, struct IA *IA, const int n_z_el)
{
    printf("\nA: ");
    print_array(A, n_z_el);

    printf("\nJA: ");
    print_array(JA, n_z_el);

    print_list(IA);

    puts(" ");
}
