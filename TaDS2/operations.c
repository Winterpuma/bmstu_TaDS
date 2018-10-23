#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "operations.h"
#include "structures.h"
#include "input.h"

#define FILE_NAME_LEN 20
#define ITERATIONS 1000

void swap(void* a, void* b, void* buf, size_t size)
{
    memcpy(buf, a, size);
    memcpy(a, b, size);
    memcpy(b, buf, size);
}


void bubble_sort(void* base, size_t num, size_t size, int (*compare)(const void*, const void*))
{
    int flag = 1;
    void* cur, * prev, * last;
    void* buf = malloc(size);

    cur = base;
    prev = base;
    last = (void*) ((char*) base + size * (num - 1));

    while (flag)
    {
        flag = 0;
        while (cur != last)
        {
            prev = cur;
            cur = (void*) ((char*) cur + size);
            if (compare(cur, prev) < 0)
            {
                swap(cur, prev, buf, size);
                flag = 1;
            }
        }

        if (!flag)
            break;

        flag = 0;

        while (prev != base)
        {
            cur = prev;
            prev = (void*) ((char*) prev - size);

            if (compare(cur, prev) < 0)
            {
                swap(cur, prev, buf, size);
                flag = 1;
            }
        }
    }

    free(buf);
}

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

    if (input_string("Input file name:\n", str, FILE_NAME_LEN) == 0)
    {
        if (load_table(&tmp_table, str) == 0)
            printf("\nSuccessfully loaded \n");
        else
        {
            printf("\nCan't load!\n");
            return;
        }

        // qsort table
        tms = 0;
        for (int i = 0; i < ITERATIONS; i++)
        {
            tm = tick();
            sort_stud_table(&tmp_table);
            tm = tick() - tm;
            tms += tm;
            load_table(&tmp_table, str);
        }

        printf("\n{ Table sorting (qsort) = %llu }\n", tms);

        // qsort key
        tms = 0;

        for (int i = 0; i < ITERATIONS; i++)
        {
            create_key_table(&tmp_table, &tmp_key_table);
            tm = tick();
            sort_key_table(&tmp_key_table);
            tm = tick() - tm;
            tms += tm;
        }

        printf("\n{ Key table sorting (qsort) = %llu }\n", tms);

        // bubble_sort table
        tms = 0;

        for (int i = 0; i < ITERATIONS; i++)
        {
            tm = tick();
            bubble_sort(tmp_table.ptr_first, tmp_table.n, sizeof(struct Car), cmp_car);
            tm = tick() - tm;
            tms += tm;

            load_table(&tmp_table, str);
        }

        printf("\n{ Table sorting (bubble sort) = %llu }\n", tms);

        // bubble_sort key
        tms = 0;

        for (int i = 0; i < ITERATIONS; i++)
        {
            create_key_table(&tmp_table, &tmp_key_table);

            tm = tick();
            bubble_sort(tmp_key_table.ptr_first, tmp_key_table.n, sizeof(struct Key), cmp_key);
            tm = tick() - tm;
            tms += tm;
        }

        printf("\n{ Key table sorting (bubble sort) = %llu }\n", tms);
        printf("\n{ Table size = %ld B }\n", sizeof(struct Student) * tmp_table.size);
        printf("\n{ Key table size = %ld B }\n", sizeof(struct Key) * tmp_key_table.n);
    }
}
/*
void search(void) {
        char str[STR_LEN];
        int found = 0;

        printf("\nSearching for used cars with mileage < 10000 km,\nno repairs and specified color...\n");
        if (input_string("\nInput color to search:\n", str, STR_LEN) == 0) {
                struct Student *ptr_cur = table.ptr_first;

                printf("\n-O Search results -O\n");

                printf("--------------------------------------------\n");

                for (int i = 0; i < table.n; i++) {
                        if (strcmp(str, ptr_cur->color) == 0) {
                                printf("[ Record %d ]\n", (i + 1));
                                print_car(ptr_cur);
                                printf("--------------------------------------------\n");

                                found++;
                        }

                        ptr_cur++;
                }

                if (found == 0) {
                        printf("  Nothing found.\n");
                        printf("--------------------------------------------\n");
                }

                printf("-O Search results end -O\n");
        }
}
*/
