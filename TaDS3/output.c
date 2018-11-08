#include <stdio.h>
#include "output.h"
#include "matrices.h"

void print_matrix(int *matr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%5d ", matr[i*m+j]);
        printf("\n");
    }
}

void dbg_print(int n, int m, int *matr, int *A, int *JA, struct IA *IA, int lenA)
{
    struct IA *tmp = IA->next;


    printf("A: ");
    for (int i=0; i<lenA; i++)
        printf("%d ", A[i]);

    printf("\nJA: ");
    for (int i=0; i<lenA; i++)
        printf("%d ", JA[i]);

    printf("\n\ni: ");
    for (; tmp->next != NULL; tmp = tmp->next)
        printf("%d ", tmp->i);

    printf("\nIA: ");
    IA = IA->next;
    for (; IA->next != NULL; IA = IA->next)
        printf("%d ", IA->Nk);
    printf("\n");

    printf("matrix:\n");
    print_matrix(matr, n, m);
}

