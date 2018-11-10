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


void convert_matrix(const int *matr, int n, int m, int *A, int *JA, int *AN, int *ANi, int n_z_el, int n_z_rows)
{
    int A_curr = 0;
    int An_curr = 0;
    int first_in_row = 1;

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
                    AN[An_curr] = A_curr;
                    ANi[An_curr] = i;
                    An_curr++;
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


void add_matrices_advanced(const int *A1, const int *JA1, const int *AN1, const int *ANi1, int n_z_el1, int n_z_rows1,
                           const int *A2, const int *JA2, const int *AN2, const int *ANi2, int n_z_el2, int n_z_rows2,
                           int *A3, int *JA3, int *AN3, int *ANi3, int *n_z_el3, int *n_z_rows3)
{
    *n_z_el3 = 0;
    *n_z_rows3 = 0;
    int curr_i1 = 0, curr_i2 = 0;

    while ((curr_i1 < n_z_rows1) && (curr_i2 < n_z_rows2))
    {
        if (ANi1[curr_i1] < ANi2[curr_i2])
        {
            copy_row(A1, JA1, AN1, ANi1, curr_i1, n_z_rows1, n_z_el1, A3, JA3, AN3, ANi3, n_z_el3, n_z_rows3);
            curr_i1++;
        }
        else if (ANi2[curr_i2] < ANi1[curr_i1])
        {
            copy_row(A2, JA2, AN2, ANi2, curr_i2, n_z_rows2, n_z_el2, A3, JA3, AN3, ANi3, n_z_el3, n_z_rows3);
            curr_i2++;
        }
        else // if equal
        {
            add_rows(A1, JA1, AN1, ANi1, curr_i1, n_z_rows1, n_z_el1, A2, JA2, AN2, ANi2, curr_i2, n_z_rows2, n_z_el2, A3, JA3, AN3, ANi3, n_z_el3, n_z_rows3);
            curr_i1++;
            curr_i2++;
        }
    }

    // if some elements left in 1 or 2
    while (curr_i1 < n_z_rows1)
    {
        copy_row(A1, JA1, AN1, ANi1, curr_i1, n_z_rows1, n_z_el1, A3, JA3, AN3, ANi3, n_z_el3, n_z_rows3);
        curr_i1++;
    }
    while (curr_i2 < n_z_rows2)
    {
        copy_row(A2, JA2, AN2, ANi2, curr_i2, n_z_rows2, n_z_el2, A3, JA3, AN3, ANi3, n_z_el3, n_z_rows3);
        curr_i2++;
    }
}


// Copy row from 1st matrix to second
void copy_row(const int *A1, const int *JA1, const int *AN1, const int *ANi1, int curr_i1, int max_i1, int max_iel,
              int *A3, int *JA3, int *AN3, int *ANi3, int *n_z_el3, int *n_z_rows3)
{
    // Determine indexes of elements to copy
    int i_from = AN1[curr_i1];
    int i_to;

    if (curr_i1 == max_i1 - 1) // if last non-zero row
        i_to = max_iel;
    else
        i_to = AN1[curr_i1 + 1];
    //NOTE do not take last one


    // Fill
    ANi3[*n_z_rows3] = ANi1[curr_i1];
    AN3[*n_z_rows3] = *n_z_el3;

    for (int i = i_from; i < i_to; i++)
    {
        A3[*n_z_el3] = A1[i];
        JA3[*n_z_el3] = JA1[i];
        (*n_z_el3)++;
    }

    (*n_z_rows3)++;
}

void add_rows(const int *A1, const int *JA1, const int *AN1, const int *ANi1, int curr_i1, int max_i1, int max_i1el,
              const int *A2, const int *JA2, const int *AN2, const int *ANi2, int curr_i2, int max_i2, int max_i2el,
              int *A3, int *JA3, int *AN3, int *ANi3, int *n_z_el3, int *n_z_rows3)
{

    ANi3[*n_z_rows3] = ANi1[curr_i1];
    AN3[*n_z_rows3] = *n_z_el3;

    // Find indexes
    int i1_from = AN1[curr_i1];
    int i1_to, i1 = i1_from;

    if (curr_i1 == max_i1 - 1) // if last non-zero row
        i1_to = max_i1el;
    else
        i1_to = AN1[curr_i1 + 1];

    int i2_from = AN2[curr_i2];
    int i2_to, i2 = i2_from;

    if (curr_i2 == max_i2 - 1) // if last non-zero row
        i2_to = max_i2el;
    else
        i2_to = AN2[curr_i2 + 1];

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
    }

    while (i2 < i2_to)
    {
        JA3[*n_z_el3] = JA2[i2];
        A3[*n_z_el3] = A2[i2++];
    }
}
