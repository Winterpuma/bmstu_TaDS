#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "output.h"
#include "matrices.h"


void generate_matrix(int *matr, int n, int m, int fill)
{
    int chance;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            chance = rand() % 100;
            if (chance > fill)
                matr[i*m+j] = 0;
            else
                matr[i*m+j] = rand() % 10;
        }
}


void input_matrix(int *matr, int n, int m)
{
    int i = 0, j = 0, value = 0;

    fflush(stdin);
    do
    {
        if (i >= 0 && j >= 0 && i < n && j < m)
            matr[i*m+j] = value;
        else
            printf("ERR: wrong index (i: [0; %d], j: [0, %d])\n", n - 1, m - 1);

        printf("Input (i j value): ");
        fflush(stdin);
    }
    while (scanf("%d %d %d", &i, &j, &value) == 3);
}


void count_non_zero(const int *matr, int n, int m, int *non_zero_rows, int *non_zero_elements)
{
    *non_zero_rows = 0;
    *non_zero_elements = 0;

    int row_counted = 0;

    for (int i = 0; i < n; i++)
    {
        row_counted = 0;
        for (int j = 0; j < m; j++)
            if (matr[i*m+j] != 0)
            {
                (*non_zero_elements)++;
                if (!row_counted)
                {
                    row_counted = 1;
                    (*non_zero_rows)++;
                }
            }
    }
}


void convert_matrix(const int *matr, int n, int m, int *A, int *JA, struct IA *IA)
{
    int A_curr = 0;
    int An_curr = 0;
    int first_in_row = 1;

// ANy rows to fill (check IA = NULL)
    for (int i = 0; i < n; i++)
    {
        first_in_row = 1;
        for (int j = 0; j < m; j++)
            if (matr[i*m+j] != 0)
            {
                A[A_curr] = matr[i*m+j];
                JA[A_curr] = j;

                if (first_in_row)
                {
                    first_in_row = 0;
                    IA->Nk = A_curr;
                    IA->i = i;
                    IA = IA->next;
                }
                A_curr++;
            }
    }
}


void add_matrices_simple(const int *matr1, const int *matr2, int *matr3, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matr3[i*m+j] = matr1[i*m+j] + matr2[i*m+j];
}


void add_matrices_advanced(const int *A1, const int *JA1, struct IA *IA1, int n_z_el1,
                           const int *A2, const int *JA2, struct IA *IA2, int n_z_el2,
                           int *A3, int *JA3, struct IA *IA3, int *n_z_el3)
{
    *n_z_el3 = 0;

    struct IA *tmp1 = IA1, *tmp2 = IA2, *tmp3 = IA3;

    while (tmp1 && tmp2)
    {
        if (tmp1->i < tmp2->i)
        {
            copy_row(A1, JA1, tmp1, n_z_el1, A3, JA3, tmp3, n_z_el3);
            tmp1 = tmp1->next;
        }
        else if (tmp2->i < tmp1->i)
        {
            copy_row(A2, JA2, tmp2, n_z_el2, A3, JA3, tmp3, n_z_el3);
            tmp2 = tmp2->next;
        }
        else
        {
            add_rows(A1, JA1, tmp1, n_z_el1, A2, JA2, tmp2, n_z_el2, A3, JA3, tmp3, n_z_el3);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        if (tmp3->next)
            tmp3 = tmp3->next;
    }

    while (tmp1)
    {
        copy_row(A1, JA1, tmp1, n_z_el1, A3, JA3, tmp3, n_z_el3);
        tmp1 = tmp1->next;

        if (tmp3->next)
            tmp3 = tmp3->next;
    }

    while (tmp2)
    {
        copy_row(A2, JA2, tmp2, n_z_el2, A3, JA3, tmp3, n_z_el3);
        tmp2 = tmp2->next;

        if (tmp3->next)
            tmp3 = tmp3->next;
    }
}


// Copy row from 1st matrix to second
void copy_row(const int *A1, const int *JA1, struct IA *IA1, int max_iel,
              int *A3, int *JA3, struct IA *IA3, int *n_z_el3)
{
    // Determine indexes of elements to copy
    int i_from = IA1->Nk;
    int i_to;

    if (IA1->next)
    {
        i_to = (IA1->next)->Nk;
    }
    else
    {
        i_to = max_iel;
    }

    // Allocate new row
    if (IA3->i != -1)
    {
        IA3->next = malloc(sizeof(struct IA));
        IA3 = IA3->next;
        IA3->next = NULL;
    }

    // Fill
    IA3->i = IA1->i;
    IA3->Nk = *n_z_el3;

    for (int i = i_from; i < i_to; i++)
    {
        A3[*n_z_el3] = A1[i];
        JA3[*n_z_el3] = JA1[i];
        (*n_z_el3)++;
    }
}

void add_rows(const int *A1, const int *JA1, struct IA *IA1, int max_i1el,
              const int *A2, const int *JA2, struct IA *IA2, int max_i2el,
              int *A3, int *JA3, struct IA *IA3, int *n_z_el3)
{
    // Allocate new row
    if (IA3->i != -1)
    {
        IA3->next = malloc(sizeof(struct IA));
        IA3 = IA3->next;
        IA3->next = NULL;
    }

    IA3->i = IA1->i;
    IA3->Nk = *n_z_el3;

    // Find indexes
    int i1_from = IA1->Nk;
    int i1_to, i1 = i1_from;

    if (IA1->next)
        i1_to = (IA1->next)->Nk;
    else
        i1_to = max_i1el;

    int i2_from = IA2->Nk;
    int i2_to, i2 = i2_from;

    if (IA2->next)
        i2_to = (IA2->next)->Nk;
    else
        i2_to = max_i2el;

    // Add rows
    while ((i1 < i1_to) && (i2 < i2_to))
    {
        if (JA1[i1] < JA2[i2])
        {
            JA3[*n_z_el3] = JA1[i1];
            A3[*n_z_el3] = A1[i1++];
        }
        else if (JA2[i2] < JA1[i1])
        {
            JA3[*n_z_el3] = JA2[i2];
            A3[*n_z_el3] = A2[i2++];
        }
        else
        {
            JA3[*n_z_el3] = JA1[i1];
            A3[*n_z_el3] = A1[i1++] + A2[i2++];
        }
        (*n_z_el3)++;
    }

    // if some elements left in 1 or 2
    while (i1 < i1_to)
    {
        JA3[*n_z_el3] = JA1[i1];
        A3[*n_z_el3] = A1[i1++];
        (*n_z_el3)++;
    }

    while (i2 < i2_to)
    {
        JA3[*n_z_el3] = JA2[i2];
        A3[*n_z_el3] = A2[i2++];
        (*n_z_el3)++;
    }
}
