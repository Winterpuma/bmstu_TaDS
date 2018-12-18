#include <stdio.h>
#include "io.h"

void input_values(int *n, int *interval, int *log, time_range *T1, time_range *T2, time_range *T3, time_range *T4)
{
    do
    {
        printf("\nInput stop queue1_out value: ");
        fflush(stdin);
    }
    while (scanf("%d", n) != 1);

    do
    {
        printf("\nShow log? 0(f)/1(t): ");
        fflush(stdin);
    }
    while (scanf("%d", log) != 1);

    if (*log)
    {
        do
        {
            printf("\nPrint log after: ");
            fflush(stdin);
        }
        while (scanf("%d", interval) != 1);
    }

    int flag = 0;
    do
    {
        printf("\nChange ranges? 0(f)/1(t): ");
        fflush(stdin);
    }
    while (scanf("%d", &flag) != 1);

    if (flag)
    {
        input_range(T1, 1);
        input_range(T2, 2);
        input_range(T3, 3);
        input_range(T4, 4);
    }
}

void input_range(time_range *T, int i)
{
    do
    {
        printf("\nInput T%d_min T%d_max  value: ", i, i);
        fflush(stdin);
    }
    while (scanf("%lf %lf", &(T->min), &(T->max)) != 2);
}

void print_values(int n, int interval, int log, time_range *T1, time_range *T2, time_range *T3, time_range *T4)
{
    printf("Stop queue1_out value is %d\n", n);

    if (log)
        printf("Show log every %d queue1_out\n", interval);
    else
        printf("Don't show log.\n");

    print_range(T1, 1);
    print_range(T2, 2);
    print_range(T3, 3);
    print_range(T4, 4);
}

void print_range(time_range *T, int i)
{
    printf("T%d_min: %lf   T%d_max: %lf \n", i, T->min, i, T->max);
}
