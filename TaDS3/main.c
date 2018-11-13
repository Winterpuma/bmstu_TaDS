#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <time.h>

#include "input.h"
#include "alloc.h"
#include "matrices.h"
#include "output.h"
#include "time_testing.h"

int main()
{
    srand(time(0));

    int option;
    int flag = 0;
    int fill = 20; // percentage of non-zero elements in matrix

    int *matr1, *matr2, *matr3;
    int n, m;
    int n_z_el1, n_z_el2, n_z_el3;
    int n_z_rows1, n_z_rows2;

    int *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = NULL, *IA2 = NULL, *IA3 = NULL, *tmp;


    printf("This program will calculate sum of int matrices.\n");

    printf("If you want to ONLY time tes input n \n");
    option = input_flag("Sum two matrices ");
    if (option)
    {
        option = input_flag("Input matrix by hand ");
        input_size("Input size of matrices (n m): ", &n, &m);

        flag = allocate_matrices(&matr1, &matr2, &matr3, n * m);
        if (flag) {
            printf("\nAllocation error.");
            return flag;
        }

        // Creation of two matrices
        if (option) {
            printf("\nIn input option. To finish input enter any non-digit char.\n");
            printf("\nInput first matrix:\n");
            input_matrix(matr1, n, m);
            printf("\nInput second matrix:\n");
            input_matrix(matr2, n, m);
        } else {
            generate_matrix(matr1, n, m, fill);
            generate_matrix(matr2, n, m, fill);
        }

        // First
        count_non_zero(matr1, n, m, &n_z_rows1, &n_z_el1);
        allocate_two_arrays(&A1, &JA1, n_z_el1);

        if (n_z_rows1) {
            IA1 = malloc(sizeof(struct IA));
            tmp = IA1;
            for (int i = 0; i < n_z_rows1 - 1; i++) {
                tmp->next = malloc(sizeof(struct IA));
                tmp = tmp->next;
            }
            tmp->next = NULL;
        }
        convert_matrix(matr1, n, m, A1, JA1, IA1);

        // Second
        count_non_zero(matr2, n, m, &n_z_rows2, &n_z_el2);
        allocate_two_arrays(&A2, &JA2, n_z_el2);

        if (n_z_rows2) {
            IA2 = malloc(sizeof(struct IA));
            tmp = IA2;
            for (int i = 0; i < n_z_rows2 - 1; i++) {
                tmp->next = malloc(sizeof(struct IA));
                tmp = tmp->next;
            }
            tmp->next = NULL;
        }

        convert_matrix(matr2, n, m, A2, JA2, IA2);


        // Addition
        allocate_two_arrays(&A3, &JA3, n_z_el1 + n_z_el2);
        //add_matrices_simple(matr1, matr2, matr3, n, m);
        IA3 = malloc(sizeof(struct IA));
        IA3->Nk = -1;
        IA3->i = -1;
        IA3->next = NULL;

        add_matrices_simple(matr1, matr2, matr3, n, m);
        add_matrices_advanced(A1, JA1, IA1, n_z_el1, A2, JA2, IA2, n_z_el2, A3, JA3, IA3, &n_z_el3);

        option = input_flag("\nOutput matrices ");
        if (option) {
            puts("\nFirst:");
            print_matrix(matr1, n, m);
            print_advanced(A1, JA1, IA1, n_z_el1);

            puts("\nSecond:");
            print_matrix(matr2, n, m);
            print_advanced(A2, JA2, IA2, n_z_el2);

            puts("\nResult:");
            print_matrix(matr3, n, m);
            print_advanced(A3, JA3, IA3, n_z_el3);
        }

        // Free memory
        free_all(matr1, A1, JA1, IA1);
        free_all(matr2, A2, JA2, IA2);
        free_all(matr3, A3, JA3, IA3);
    }

    // Time testing
    fflush(stdin);
    option = input_flag("\nTime testing ");

    if (option)
    {
        puts("Time testing: ");
        puts(" #elements | fill | Simple:   time           size | Advanced:  time         size");
        time_testing(10, 10, 5);
        time_testing(10, 10, 20);
        time_testing(10, 10, 50);
        time_testing(100, 100, 5);
        time_testing(100, 100, 20);
        time_testing(100, 100, 50);
        time_testing(1000, 1000, 5);
        time_testing(1000, 1000, 20);
        time_testing(1000, 1000, 50);
        time_testing(1000, 1000, 90);
    }

    //option = input_flag("");
    return 0;
}