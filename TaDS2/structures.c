#include <stdio.h>

#include "input.h"
#include "structures.h"

int load_table()
{
    return 0;
}

int save_table()
{
    return 0;
}

int input_student(struct Student *stud)
{
    input_string("Input Name:", stud->name, LEN_NAME);
    input_bool("Input sex (0-female, 1-male): ", &(stud->sex));
    input_number("Input age", &(stud->age), 10, 70);
    input_number("Input average grade", &(stud->average_grade), 0, 100);
    input_number("Input admission_year", &(stud->admission_year), 1500, 2018);
    input_bool("Input house type (0-home, 1-hostel): ", &(stud->house_type));

    return 0;
}

void output_student(struct Student *stud)
{
    printf("\nStudent %s\n", stud->name);

    printf("Sex: ");
    if (stud->sex)
        printf("male\n");
    else
        printf("female\n");

    printf("Age: %d\n", stud->age);
    printf("Average grade: %d\n", stud->average_grade);
    printf("Admission_year: %d\n", stud->admission_year);

    printf("House type: ");
    if (stud->house_type)
        printf("hostel\n");
    else
        printf("home\n");
}
