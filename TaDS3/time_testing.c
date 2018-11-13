#include <stdio.h>
#include <stdlib.h>
#include "time_testing.h"
#include "alloc.h"
#include "matrices.h"

#define ITER 10

unsigned long long tick(void)
{
    unsigned long long tmp;
    __asm__ __volatile__ ("rdtsc" : "=A" (tmp) );
    return tmp;
}

void time_testing(int n, int m, int fill)
{
    unsigned long long time_b, time_e;

    int *matr1, *matr2, *matr3;
    int n_z_el1, n_z_el2, n_z_el3;
    int n_z_rows1, n_z_rows2, n_z_rows3;

    int *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = NULL, *IA2 = NULL, *IA3 = NULL, *tmp;

    puts("--------------------------------------------------------------");
    printf("%10d |%5d |", n*m, fill);

    // Simple addition
    allocate_matrices(&matr1, &matr2, &matr3, n*m);
    generate_matrix(matr1, n, m, fill);
    generate_matrix(matr2, n, m, fill);

    time_b = tick();
    for (int i = 0; i < ITER; i++)
        add_matrices_simple(matr1, matr2, matr3, n, m);
    time_e = tick();
    printf("%15d (%12dB)|", (time_e - time_b)/ITER, sizeof(int)*n*m*3);

    // Advanced addition
    count_non_zero(matr1, n, m, &n_z_rows1, &n_z_el1);
    allocate_two_arrays(&A1, &JA1, n_z_el1);

    if (n_z_rows1)
    {
        IA1 = malloc(sizeof(struct IA));
        tmp = IA1;
        for (int i = 0; i < n_z_rows1 - 1; i++) {
            tmp->next = malloc(sizeof(struct IA));
            tmp = tmp->next;
        }
        tmp->next = NULL;
    }

    convert_matrix(matr1, n, m, A1, JA1, IA1);

    count_non_zero(matr2, n, m, &n_z_rows2, &n_z_el2);
    allocate_two_arrays(&A2, &JA2, n_z_el2);

    if (n_z_rows2)
    {
        IA2 = malloc(sizeof(struct IA));
        tmp = IA2;
        for (int i = 0; i < n_z_rows2 - 1; i++) {
            tmp->next = malloc(sizeof(struct IA));
            tmp = tmp->next;
        }
        tmp->next = NULL;
    }


    convert_matrix(matr2, n, m, A2, JA2, IA2);

    allocate_two_arrays(&A3, &JA3, n_z_el1 + n_z_el2);

    IA3 = malloc(sizeof(struct IA));
    IA3->Nk = -1;
    IA3->i = -1;
    IA3->next = NULL;

    time_b = tick();
    for (int i = 0; i < ITER; i++)
        add_matrices_advanced(A1, JA1, IA1, n_z_el1, A2, JA2, IA2, n_z_el2, A3, JA3, IA3, &n_z_el3);
    time_e = tick();

    count_non_zero(matr3, n, m, &n_z_rows3, &n_z_el3);

    int size1 = sizeof(int)*n_z_el1*2 + sizeof(struct IA)*n_z_rows1;
    int size2 = sizeof(int)*n_z_el2*2 + sizeof(struct IA)*n_z_rows2;
    int size3 = sizeof(int)*n_z_el3*2 + sizeof(struct IA)*n_z_rows3;

    printf("%15d (%12dB)\n", (time_e - time_b)/ITER, size1 + size2 + size3);
}