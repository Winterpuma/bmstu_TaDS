#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <time.h>

#include "input.h"
#include "alloc.h"

int main()
{
    srand(time(0));
    int option, lenA1 = 0, lenA2 = 0, lenA3 = 0;
    int *matr1, *matr2, *matr3;
    int n, m;
    int *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = create(-1, -1), *IA2 = create(-1, -1), *IA3 = create(-1, -1);
    int count1 = 0, count2 = 0; // amount of non-zero lines
    int fill = 20; // percentage of non-zero elements in matrix

    printf("This programm will calculate summ of int matrices.\n");

    option = input_flag("Input matrix by hand ");
    input_size("Input size of matrices (n m): ", &n, &m);

    // Creation of two matrices
    if (option)
    {
        allocate_matr(&matr1, &A1, &JA1, n, m);
        matrInput(n, m, matr1, A1, JA1, IA1, &lenA1);

        fflush(stdin);
        allocate_matr(&matr2, &A2, &JA2, n, m);
        matrInput(n, m, matr2, A2, JA2, IA2, &lenA2);
    }
    else
    {
        allocate_gen_matr(&matr1, &A1, &JA1, n, m, &count1, fill);
        matrDefault(matr1, n, m,A1,JA1,IA1, &lenA1);
        print(n,m, matr1, A1, JA1, IA1, lenA1);

        allocate_gen_matr(&matr2, &A2, &JA2, n, m, &count2, fill);
        matrDefault(matr2, n, m,A2,JA2,IA2, &lenA2);
        print(n,m, matr2, A2, JA2, IA2, lenA2);
    }


    // Addition
    allocate_matr(&matr3, &A3, &JA3, n, m);

    Plus_R(n, m, A1, A2, JA1, JA2, IA1, IA2, lenA1, lenA2, A3, JA3, IA3, &lenA3);
    summtrix(matr1, matr2, matr3, n, m);
    print(n,m, matr3, A3, JA3, IA3, lenA1);

    // Output results
    option = input_flag("Print matrices ");
    if (option)
    {
       printf("\nFirst matrix:\n");
       printmatrix(matr1, n, m);
       printf("\nSecord matrix:\n");
       printmatrix(matr2, n, m);
       printf("\nResult matrix:\n");
       printmatrix(matr3, n, m);
    }

    // Free memory
    free_all(IA1);
    free_all(IA2);
    free_all(IA3);
    free(A1);
    free(A2);
    free(A3);
    free(JA1);
    free(JA2);
    free(JA3);
    free(matr1);
    free(matr2);
    free(matr3);


/*
    // Time testing
    fflush(stdin);
    option = input_flag("Time testing: ");

    if (option)
    {
        time_test(5);
        time_test(15);
        time_test(25);
    }
*/

    return 0;
}

