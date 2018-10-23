#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "structures.h"
#include "input.h"

#define EXIT -1
#define ITERATIONS 1000
#define FILE_NAME_LEN 30

struct StudentTable stTbl = {NULL, 0, 0};
struct KeyTable keyTbl ={NULL, 0};

void swap(void* a, void* b, void* buf, size_t size);
void bubble_sort(void* base, size_t num, size_t size, int (*compare)(const void*, const void*));
unsigned long long tick(void);
void measure_sorting_time();

/*
Вариант 18
Tanya

Type жилье = (дом, общежитие);
 Данные:
    имя, пол (м, ж), возраст, средний балл за сессию, дата поступления
 адрес:
    дом : (улица, №дома, №кв );
    общежитие : (№общ., №комн.);

Ввести общий список студентов группы.
Вывести список студентов, живущих в общежитии указанного года
поступления.
*/

int menu()
{
    int operation = 0;
    int tmp;
    char name[LEN_NAME];

    struct Student tmp_stud;

    printf("\nMENU (choose operation):\n\t"
           "1 - Load from file\n\t"
           "2 - Save to file\n\t"
           "3 - Add record\n\t"
           "4 - Remove record\n\t"
           "5 - Sort table\n\t"
           "6 - Print table\n\t"
           "7 - Create key table\n\t"
           "8 - Sort key table\n\t"
           "9 - Print key table\n\t"
           "10 - Print table in key order\n\t"
           "11 - Search\n\t"
           "12 - Measure sorting time\n\t"
           "0 - Exit\n");
    fflush(stdin);

    if (scanf("%d", &operation) == 1)
    {
        if (operation == 0)
        {
            clear_table(&stTbl);
            return EXIT;
        }
        else if (operation == 1)
        {
            puts("Load");
            input_string("Input file name: ", name, LEN_NAME);
            FILE *in = fopen(name, "r");
            if (load_table(in, &stTbl) == 0) //NOTE
                printf("Loaded.\n");
            else
                printf("Loading error.\n");
            fclose(in);
        }
        else if (operation == 2)
        {
            input_string("Input file name: ", name, LEN_NAME);
            FILE *out = fopen(name, "w");
            save_table(out, &stTbl);
            fclose(out);
        }
        else if (operation == 3)
        {
            input_student(&tmp_stud); //Record to table NOTE
            add_to_table(&stTbl, &tmp_stud);

        }
        else if (operation == 4)
        {
            input_number("Input index of student to delete", &tmp, 1, stTbl.size);
            remove_from_table(&stTbl, tmp);
        }
        else if (operation == 5)
        {
            sort_stud_table(&stTbl);
        }
        else if (operation == 6)
        {
            output_stTable_console(&stTbl);
        }
        else if (operation == 7)
        {
            create_key_table(&stTbl, &keyTbl);
            printf("Key table was created.");
        }
        else if (operation == 8)
        {
            sort_key_table(&keyTbl);
        }
        else if (operation == 9)
        {
            print_key_table(&keyTbl);
        }
        else if (operation == 10)
        {
            print_stud_table_by_key(&stTbl, &keyTbl);
        }
        else if (operation == 12)
        {
            measure_sorting_time();

        }
        else
            printf("Invalid input.\n");
    }
    else
    {
        printf("\nInvalid input.\n");
    }
    return 0;
}


int main(void)
{
        while (menu() == 0);

        return 0;
}

void swap(void* a, void* b, void* buf, size_t size)
{
    memcpy(buf, a, size);
    memcpy(a, b, size);
    memcpy(b, buf, size);
}


void bubble_sort(void *base, size_t num, size_t size, int (*compare)(const void*, const void*))
{
    int flag = 1;
    void *cur, *prev, *last;
    void *buf = malloc(size);

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
            printf("here1");
            if (compare(cur, prev) < 0)
            {
                printf("2");
                swap(cur, prev, buf, size);
                flag = 1;
            }
            printf("3");
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

    input_string("Input file name:\n", str, FILE_NAME_LEN);

    if (1)
    {
        FILE *in = fopen(str, "r");
        if (load_table(in, &tmp_table) == 0)
            printf("\nSuccessfully loaded \n");
        else
        {
            printf("\nCan't load!\n");
            return;
        }
        rewind(in);

        // qsort table
        tms = 0;
        for (int i = 0; i < ITERATIONS; i++)
        {
            //printf("fl");
            tm = tick();
            sort_stud_table(&tmp_table);
            tm = tick() - tm;
            tms += tm;
            load_table(in, &tmp_table);
            rewind(in);
        }

        printf("\n{ Table sorting (qsort) = %I64d }\n", tms);

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

        printf("\n{ Key table sorting (qsort) = %I64d }\n", tms);

        // bubble_sort table
        tms = 0;

        for (int i = 0; i < ITERATIONS; i++)
        {
            tm = tick();
            bubble_sort(tmp_table.ptr_first, tmp_table.size, sizeof(struct Student), cmp_stud);
            tm = tick() - tm;
            tms += tm;

            load_table(in, &tmp_table);
            rewind(in);
        }

        printf("\n{ Table sorting (bubble sort) = %I64d }\n", tms);

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

        printf("\n{ Key table sorting (bubble sort) = %I64d }\n", tms);
        printf("\n{ Table size = %I64d B }\n", sizeof(struct Student) * tmp_table.size);
        printf("\n{ Key table size = %I64d B }\n", sizeof(struct Key) * tmp_key_table.n);
        fclose(in);
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

