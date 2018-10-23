#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "structures.h"


// ------------- Student
int input_student(struct Student *stud)
{
    input_string("Input Name:", stud->name, LEN_NAME);
    input_bool("Input sex (0-female, 1-male): ", &(stud->sex));
    input_number("Input age", &(stud->age), 10, 70);
    input_number("Input average grade", &(stud->average_grade), 0, 100);
    input_number("Input admission_year", &(stud->admission_year), 1500, 2018);
    input_bool("Input house type (0-home, 1-hostel): ", &(stud->house_type));

    if (stud->house_type)
    {
        input_number("Input hostel number", &(stud->adress.hostel.hostel_num), 1, 100);
        input_number("Input room number", &(stud->adress.hostel.room_num), 1, 100);
    }
    else
    {
        input_string("Street name: ", stud->adress.home_adress.street, LEN_STREET);
        input_number("Input house number", &(stud->adress.home_adress.house_num), 1, 1000);
        input_number("Input appartment number", &(stud->adress.home_adress.appartment_num), 1, 1000);
    }

    return 0;
}


struct Student *input_student_file(FILE *f)
{
    struct Student *stud = (struct Student*)malloc(sizeof(struct Student));
    int flag = 0;
    if (fscanf(f, "%[^\n]\n", stud->name) != 1) flag = -1;
    if (fscanf(f, "%d", &stud->sex) != 1) flag = -1;
    if (fscanf(f, "%d", &stud->age) != 1) flag = -1;
    if (fscanf(f, "%d", &stud->average_grade) != 1) flag = -1;
    if (fscanf(f, "%d", &stud->admission_year) != 1) flag = -1;
    if (fscanf(f, "%d", &stud->house_type) != 1) flag = -1;

    if (stud->house_type) // if hostel
    {

        if (fscanf(f, "%d", &stud->adress.hostel.hostel_num) != 1) flag = -1;
        if (fscanf(f, "%d", &stud->adress.hostel.room_num) != 1) flag = -1;
    }
    else
    {
        if (fscanf(f, "\n%[^\n]\n", stud->adress.home_adress.street) != 1)
        {
            flag = -1;
            //printf("something wrong");
        }
        //printf("SCANF %s\n", stud->adress.home_adress.street);
        if (fscanf(f, "%d", &stud->adress.home_adress.house_num) != 1) flag = -1;
        if (fscanf(f, "%d", &stud->adress.home_adress.appartment_num) != 1) flag = -1;
    }
    //fscanf(f, "\n"); // NOTE
    (void)flag;
    return stud;
}


void output_student_console(struct Student stud)
{
    printf("\nStudent: %s\n", stud.name);

    printf("Sex: ");
    if (stud.sex)
        printf("male\n");
    else
        printf("female\n");

    printf("Age: %d\n", stud.age);
    printf("Average grade: %d\n", stud.average_grade);
    printf("Admission_year: %d\n", stud.admission_year);

    printf("House type: ");
    if (stud.house_type)
    {
        printf("hostel\n");
        printf("Hostel number: %d\n", stud.adress.hostel.hostel_num);
        printf("Room number: %d\n", stud.adress.hostel.room_num);
    }
    else
    {
        printf("home\n");
        printf("Street: %s\n", stud.adress.home_adress.street);
        printf("House number: %d\n", stud.adress.home_adress.house_num);
        printf("House appartment number: %d\n", stud.adress.home_adress.appartment_num);
    }
}


void output_student_file(FILE *f, struct Student stud)
{
    fprintf(f, "%s\n", stud.name);
    fprintf(f, "%d\n", stud.sex);

    fprintf(f, "%d\n", stud.age);
    fprintf(f, "%d\n", stud.average_grade);
    fprintf(f, "%d\n", stud.admission_year);

    fprintf(f, "%d\n", stud.house_type);
    if (stud.house_type)
    {
        fprintf(f, "%d\n", stud.adress.hostel.hostel_num);
        fprintf(f, "%d\n", stud.adress.hostel.room_num);
    }
    else
    {
        fprintf(f, "%s\n", stud.adress.home_adress.street);
        fprintf(f, "%d\n", stud.adress.home_adress.house_num);
        fprintf(f, "%d\n", stud.adress.home_adress.appartment_num);
    }
    fprintf(f, "\n");
}
// Student -------------


// ------------- Table
int load_table(FILE *f, struct StudentTable *tbl)
{
    int size;

    if (!f)
        return -1;

    clear_table(tbl);

    if (fscanf(f, "%d\n\n", &size) != 1)
        return -2;

    for (int i = 0; i < size; i++)
    {
        fscanf(f, "\n");
        add_to_table(tbl, input_student_file(f));
    }

    fclose(f);

    return 0;
}


int save_table(FILE *f, struct StudentTable *tbl)
{
    struct Student *ptr_cur = tbl->ptr_first;
    fprintf(f, "%d\n\n", tbl->size);

    for (int i = 0; i < tbl->size; i++)
    {
        output_student_file(f, *ptr_cur);
        ptr_cur++;
    }

    return 0;
}


void output_stTable_console(struct StudentTable *tbl)
{
    struct Student *ptr_cur = tbl->ptr_first;
    printf("\nTable:\n");

    if (!tbl->size)
        puts("Table is empty!");
    else
    {
        printf("--------------------------------------------\n");
        for (int i = 0; i < tbl->size; i++)
        {

            printf("[ Student %d ]\n", (i + 1));
            output_student_console(*ptr_cur);
            printf("--------------------------------------------\n");
            ptr_cur++;
        }
    }
}


int add_to_table(struct StudentTable *tbl, const struct Student *stud)
{

    if (tbl->size >= tbl->size_max)
    {
        struct Student *ptr_free = tbl->ptr_first;
        struct Student *ptr_tmp = tbl->ptr_first;

        tbl->size_max += MALLOC_STEP;

        struct Student *ptr_new = (struct Student*) malloc(tbl->size_max * sizeof(struct Student));

        if (!ptr_new)
            return -1;

        tbl->ptr_first = ptr_new;

        for (int i = 0; i < tbl->size; i++)
        {
            *ptr_new = *ptr_tmp;
            ptr_tmp++;
            ptr_new++;
        }
        free(ptr_free);
    }

    tbl->size++;
    tbl->ptr_first[tbl->size - 1] = *stud;

    return 0;
}


int remove_from_table(struct StudentTable *tbl, int i) //?
{
    if (i > 0 && i <= tbl->size)
    {
        tbl->ptr_first[i-1] = tbl->ptr_first[tbl->size-1];
        tbl->size--;
        return 0;
    }
    else
        return -1;
}


void clear_table(struct StudentTable *tbl)
{
    tbl->size = 0;
    tbl->size_max = 0;

    if (tbl->ptr_first)
    {
        free(tbl->ptr_first);
        tbl->ptr_first = NULL;
    }
}


int cmp_stud(const void *a, const void *b)
{
    return ((struct Student*) a)->admission_year - ((struct Student*) b)->admission_year;
}

void sort_stud_table(struct StudentTable *tbl)
{
    qsort(tbl->ptr_first, tbl->size, sizeof(struct Student), cmp_stud);
}


// Table -------------


// ------------- Key Table
int create_key_table(struct StudentTable* arr_stud, struct KeyTable* arr_keys)
{
    struct Student *ptr_s;
    struct Key *ptr_key;

    clear_key_table(arr_keys);

    arr_keys->n = arr_stud->size;

    arr_keys->ptr_first = (struct Key*) malloc(sizeof(struct Key) * arr_keys->n);

    if (arr_keys->ptr_first == NULL)
        return -1; // Error in malloc
    ptr_s = arr_stud->ptr_first;
    ptr_key = arr_keys->ptr_first;
    for (int i = 0; i < arr_keys->n; i++)
    {
        ptr_key->id = i;
        ptr_key->key = ptr_s->admission_year;
        ptr_key++;
        ptr_s++;
    }

    return 0;
}

void clear_key_table(struct KeyTable* arr_keys)
{
    if (arr_keys->ptr_first != NULL)
    {
        free(arr_keys->ptr_first);
        arr_keys->ptr_first = NULL;
    }
    arr_keys->n = 0;
}

void print_key_table(const struct KeyTable* arr_keys)
{
    printf("\nKey table:\n");

    if (arr_keys->n <= 0)
        printf("Key table is empty.\n");
    else
    {
        struct Key* ptr_key = arr_keys->ptr_first;

        printf("--------------------------------------------\n");
        for (int i = 0; i < arr_keys->n; i++)
        {
            printf("ID:   %d\n", ptr_key->id + 1);
            printf("Key:  %d\n", ptr_key->key);
            printf("--------------------------------------------\n");

            ptr_key++;
        }
    }

}

int print_stud_table_by_key(const struct StudentTable* arr_stud, const struct KeyTable* arr_keys)
{
    struct Key* ptr_key = arr_keys->ptr_first;

    if (arr_keys-> n != arr_stud->size)
    {
        printf("Different sizes of arrays.\nTry to create key table first (7)\n");
        return -1; // Different sizes
    }

    printf("\nTable in key order:\n");

    if (arr_stud->size == 0)
                printf("Table is empty.\n");
    else
    {
        printf("--------------------------------------------\n");

        for (int i = 0; i < arr_keys->n; i++)
        {
            if (ptr_key->id<0 || ptr_key->id>(arr_stud->size - 1))
                return -2; // Invalid ID found

            printf("[ Student %d ]\n", (i + 1));
            output_student_console(arr_stud->ptr_first[ptr_key->id]);
            printf("--------------------------------------------\n");

            ptr_key++;
            }
    }

    return 0;
}

int cmp_key(const void *key1, const void  *key2)
{
    return ((struct Key*) key1)->key - ((struct Key*) key2)->key;
}

void sort_key_table(struct KeyTable *arr_keys)
{
    qsort(arr_keys->ptr_first, arr_keys->n, sizeof(struct Key), cmp_key);
}



// Key Table -------------
