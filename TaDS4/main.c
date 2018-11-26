#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"
#include "list_stack.h"
#include "parentheses.h"
#include "analysis.h"

#define N 5

int main()
{
    int operation, result;
    char ch;

    char arrStack[N];
    char *p_curr = arrStack - 1;

    struct node *last_element = NULL;
    init_free_area();

    while (1)
    {
        operation = 0;

        printf("\nMENU (choose operation):\n\t"
               "0 - Exit\n\t"
               "1 - Check expression for correctness\n\t"
               "8 - Time analysis\n"
               "Array stack:\n\t"
               "2 - Push to array stack\n\t"
               "3 - Pop from stack\n\t"
               "4 - Output stack\n"
               "List stack:\n\t"
               "5 - Push to stack\n\t"
               "6 - Pop from stack\n\t"
               "7 - Output stack\n");

        fflush(stdin);

        if (scanf("%d", &operation) == 1)
        {
            switch (operation)
            {
                case 0:
                    return 0;
                case 1:
                    result = check_parentheses();
                    if (!result)
                        printf("Correct expression.\n");
                    else
                        printf("Incorrect expression.\n");
                    break;
                case 2:
                    printf("Input single char: ");
                    fflush(stdin);
                    ch = getchar();
                    push_arr(&p_curr, arrStack + N - 1, ch);
                    break;
                case 3:
                    result = pop_arr(&p_curr, arrStack);
                    if (result == -1)
                        printf("Array is empty.\n");
                    break;
                case 4:
                    print_arr(arrStack, p_curr);
                    break;
                case 5:
                    printf("Input single char: ");
                    fflush(stdin);
                    ch = getchar();
                    last_element = push_list(last_element, ch, 1);
                    break;
                case 6:
                    last_element = pop_list(last_element, 1);
                    break;
                case 7:
                    print_list(last_element);
                    break;
                case 8:
                    analise();
                    break;
                default:
                    printf("Invalid input.\n");
                    break;
            }

        }
        else
            printf("\nInvalid input.\n");
    }
}