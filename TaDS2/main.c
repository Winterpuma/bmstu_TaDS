#include <stdio.h>
#include "operations.h"
#include "input.h"


#define EXIT -1
#define LEN_NAME 20

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

struct student
{
    char *name;
    int sex;
    int age;
    int average_grade;
    int admission_year;

    union
    {
        struct {
            char *street;
            int house_num;
            int appartment_num;
        } home_adress;

        struct{
            int hostel_num;
            int room_num;
        } hostel;

    } agress;

};

int menu()
{
    int operation = 0;
    char name[LEN_NAME];

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
        printf("Good: %d\n", operation);
        if (operation == 0)
            return EXIT;
        else if (operation == 1)
        {    // Load
            puts("Load");
            input_string("Input name: ", name, LEN_NAME);
            printf("%s", name);
        }
        else
            printf("Invalid input\n");
    }
    else
    {
        printf("\n{ Invalid input }\n");
    }
    return 0;
}


int main(void) {
        while (menu() == 0);

        return 0;
}

