#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "output.h"
#include "matrices.h"

void generate_matrix(int **matr, int n, int m, int fill)
{
    int chance;
    srand(time(0));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            chance = rand() % 100;
            if (chance > fill)
                (*matr)[i*m+j] = 0;
            else
                (*matr)[i*m+j] = rand() % 10;
        }

    print_matrix(*matr, n, m);
}

void input_matrix(int **matr, int n, int m)
{
    int i = 0, j = 0, value = 0;

    do
    {
        if (i < n && j < m)
            (*matr)[i*m+j] = value;
        else
            printf("\nERR: wrong index (i: [0; %d], j: [0, %d])", n - 1, m - 1);

        printf("\nInput (i j value): ");
        fflush(stdin);
    }
    while (scanf("%d %d", &i, &j, &value) == 3);

    print_matrix(*matr, n, m);
}

/*
int matrInput(int n, int m, int *matr, int *A, int *JA, struct IA *IA, int *lenA)
{
    int i, j, t;
    float t1;
    struct IA *tmp, *tmp1, *tmp2;

    do
    {
        printf("\nInput (i j value): ");
        while (1)
        {
            if (scanf("%d %d %d", &i, &j, &t1) != 3)
            {
                printf("\nERR: try again: ");
                fflush(stdin);
            }
            else if (i < 0 || i >= n || j < 0 || j > m)
                printf("ERR: index out of range. Try again \n");
            else break;
        }

        matr[i*m+j] = t1;

        t1 = matr[i*m+j];
        tmp = IA;
        while (tmp != NULL)
        {
            if (tmp->i != i)
            {
                tmp1 = tmp;
                tmp = tmp->next;
            }
            else
            {
                if (JA[tmp->Nk] > j)
                {
                   for (int k=*lenA; k>tmp->Nk; k--)
                   {
                       A[k] = A[k-1];
                       JA[k] = JA[k-1];
                       tmp2 = IA;
                       while (tmp2 != NULL)
                       {
                           if (tmp2->Nk != k-1 || tmp->Nk == k-1)
                               tmp2 = tmp2->next;
                           else
                           {
                               tmp2->Nk += 1;
                               break;
                           }
                       }
                   }
                   A[tmp->Nk] = t1;
                   JA[tmp->Nk] = j;
                }
                else
                {
                    for (int k=*lenA; k>tmp->Nk+1; k--)
                    {
                        A[k] = A[k-1];
                        JA[k] = JA[k-1];
                        tmp2 = IA;
                        while (tmp2 != NULL)
                        {
                            if (tmp2->Nk != k-1)
                                tmp2 = tmp2->next;
                            else
                            {
                                tmp2->Nk += 1;
                                break;
                            }
                        }
                    }
                    A[tmp->Nk+1] = t1;
                    JA[tmp->Nk+1] = j;
                }
                break;
            }
        }
        if (tmp == NULL)
        {
            A[*lenA] = t1;
            JA[*lenA] = j;
            tmp1 = add(tmp1, i, *lenA);
        }

        *lenA += 1;

        printf("Continue input? (any letter - no, numbers - yes):\n");
    }
    while (scanf("%d", &t) != 0);

    while (IA->next != NULL)
        IA = IA->next;
    add(IA, n, *lenA);

    return 0;
}


void matrDefault(float *matr, int n, int m,float *A, int *JA, struct IA *IA, int *lenA)
{
    struct IA *tmp, *tmp1, *tmp2;
    int t1;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            if (matr[i*m+j] != 0)
            {
                //A[k] = matr[i*m+j];
                //JA[k] = j;
                //k++;
                t1 = matr[i*m+j];
                tmp = IA;
                while (tmp != NULL)
                {
                    if (tmp->i != i)
                    {
                        tmp1 = tmp;
                        tmp = tmp->next;
                    }
                    else
                    {
                        if (JA[tmp->Nk] > j)
                        {
                           for (int k=*lenA; k>tmp->Nk; k--)
                           {
                               A[k] = A[k-1];
                               JA[k] = JA[k-1];
                               tmp2 = IA;
                               while (tmp2 != NULL)
                               {
                                   if (tmp2->Nk != k-1 || tmp->Nk == k-1)
                                       tmp2 = tmp2->next;
                                   else
                                   {
                                       tmp2->Nk += 1;
                                       break;
                                   }
                               }
                           }
                           A[tmp->Nk] = t1;
                           JA[tmp->Nk] = j;
                        }
                        else
                        {
                            for (int k=*lenA; k>tmp->Nk+1; k--)
                            {
                                A[k] = A[k-1];
                                JA[k] = JA[k-1];
                                tmp2 = IA;
                                while (tmp2 != NULL)
                                {
                                    if (tmp2->Nk != k-1)
                                        tmp2 = tmp2->next;
                                    else
                                    {
                                        tmp2->Nk += 1;
                                        break;
                                    }
                                }
                            }
                            A[tmp->Nk+1] = t1;
                            JA[tmp->Nk+1] = j;
                        }
                        break;
                    }
                }
                if (tmp == NULL)
                {
                    A[*lenA] = t1;
                    JA[*lenA] = j;
                    tmp1 = add(tmp1, i, *lenA);
                }

                *lenA += 1;

            }
        }
    while (IA->next != NULL)
        IA = IA->next;
    add(IA, n, *lenA);
}

*/

