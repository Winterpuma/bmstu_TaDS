#include <stdio.h>
#include "array_stack.h"
#include "list_stack.h"

#define N 5

int main()
{
    int operation;

    char arrStack[N];
    char *p_curr = arrStack - 1;

    struct node *last_element = NULL;

    while (1)
    {
        operation = 0;

        printf("\nMENU (choose operation):\n\t"
               "0 - Exit\n\t"
               "1 - Check expression for\n"
               "Array stack:\n\t"
               "2 - Add to array stack\n\t"
               "3 - Remove from stack\n\t"
               "4 - Output stack\n"
               "List stack:\n\t"
               "5 - Add to stack\n\t"
               "6 - Remove from stack\n\t"
               "7 - Output stack\n");

        fflush(stdin);

        if (scanf("%d", &operation) == 1)
        {
            switch (operation)
            {
                case 0:
                    return 0;
                case 2:
                    add_to_arr(&p_curr, arrStack + N - 1, '1');
                    break;
                case 3:
                    remove_from_arr(&p_curr, arrStack);
                    break;
                case 4:
                    print_arr(arrStack, p_curr);
                    break;
                case 5:
                    last_element = add_to_list(last_element);
                    break;
                case 6:
                    last_element = remove_from_list(last_element);
                    break;
                case 7:
                    print_list(last_element);
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