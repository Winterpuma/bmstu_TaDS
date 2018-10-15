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
            printf("something wrong");
        }
        printf("SCANF %s\n", stud->adress.home_adress.street);
        if (fscanf(f, "%d", &stud->adress.home_adress.house_num) != 1) flag = -1;
        if (fscanf(f, "%d", &stud->adress.home_adress.appartment_num) != 1) flag = -1;
    }
    //fscanf(f, "\n"); // NOTE
    (void)flag;
    output_student_console(*stud);
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

void output_student_file(FILE *f, struct Student *stud)
{
    ;
}
// Student -------------


// ------------- Table
int load_table(FILE *f, struct StudentTable *tbl)
{
    int size;
    //int flag = 1;

    if (!f)
        return -1;

    // clear_table(tbl); NOTE
    fscanf(f, "%d\n\n", &size); // обработка корректности NOTE

    for (int i = 0; i < size; i++)
    {
        fscanf(f, "\n");
        add_to_table(tbl, input_student_file(f));
    }

    fclose(f);

    return 0;
}

int save_table(struct StudentTable *tbl, FILE *f)
{
    return 0;
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
// Table -------------


// ------------- Key Table

// Key Table -------------
