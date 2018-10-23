#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sort.h"
#include "input.h"
#include "structures.h"

#define ITERATIONS 100
#define FILE_NAME_LEN 30

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void measure_sorting_time()
{
    char str[FILE_NAME_LEN];
    struct StudentTable tmp_table = {NULL, 0, 0};
    struct KeyTable tmp_key_table = {NULL, 0};
    unsigned long long tm, tms;

    input_string("Input file name:\n", str, FILE_NAME_LEN);

    FILE *in = fopen(str, "r");

    if (load_table(in, &tmp_table) == 0)
        printf("\nSuccessfully loaded\n");
    else
    {
        printf("\nCan't load\n");
        return;
    }
    printf("\n                   Table           Keys\n\n");

    printf("QSORT   :");
    //qsort table
    tms = 0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        tm = tick();
        sort_stud_table(&tmp_table);
        tm = tick() - tm;
        tms += tm;
        in = fopen(str, "r");
        load_table(in, &tmp_table);
        fclose(in);
    }
    printf("%15lld", tms/ITERATIONS);

    //qsort table
    tms = 0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        create_key_table(&tmp_table, &tmp_key_table);
        tm = tick();
        sort_key_table(&tmp_key_table);
        tm = tick() - tm;
        tms += tm;
    }
    printf("%15lld", tms/ITERATIONS);

    printf("\nMYSORT  :");
    // mysort table
    tms = 0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        tm = tick();
        mysort_stud(tmp_table.ptr_first, tmp_table.size);
        tm = tick() - tm;
        tms += tm;
        in = fopen(str, "r");
        load_table(in, &tmp_table);
        fclose(in);
    }
    printf("%15lld", tms/ITERATIONS);

    // mysort key
    tms = 0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        create_key_table(&tmp_table, &tmp_key_table);
        tm = tick();
        mysort_keys(tmp_key_table.ptr_first, tmp_key_table.n);
        tm = tick() - tm;
        tms += tm;
    }

    printf("%15lld\n", tms/ITERATIONS);

    printf("\nSIZE    : %14lld B", sizeof(struct Student) * tmp_table.size);
    printf("%13lld B\n", sizeof(struct Key) * tmp_key_table.n);
    fclose(in);
}


void swap_students(struct Student *a, struct Student *b)
{
    struct Student tmp = *a;
    *a = *b;
    *b = tmp;
}


void mysort_stud(struct Student *base, int nitems)
{
    struct Student *pb = (struct Student *)base;
    struct Student *pe = pb + nitems;

    for (int i = 0; i < nitems; i++)
    {
        for (int j = 0; j < (pe - pb) - 1; j++)
            if (cmp_stud((void*)(pb + j), (void*)(pb + j+1)) >= 0)
            {
                swap_students((pb + j), (pb + j+1));
            }
        pe--;
    }
}


void swap_keys(struct Key *a, struct Key *b)
{
    struct Key tmp = *a;
    *a = *b;
    *b = tmp;
}

void mysort_keys(struct Key *base, size_t nitems)
{
    struct Key *pb = (struct Key *)base;
    struct Key *pe = pb + nitems;

    for (int i = 0; i < nitems; i++)
    {
        for (int j = 0; j < (pe - pb) - 1; j++)
            if (cmp_key((void*)(pb + j), (void*)(pb + j+1)) >= 0)
            {
                swap_keys((pb + j), (pb + j+1));
            }
        pe--;
    }
}
