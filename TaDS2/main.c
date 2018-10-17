#include <stdio.h>
#include "structures.h"
#include "input.h"

#define EXIT -1

struct StudentTable stTbl = {NULL, 0, 0};
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
        printf("Good: %d\n", operation);
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
        else if (operation == 6)
        {
            output_stTable_console(&stTbl);
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
