#include <stdio.h>
#include "list_stack.h"
#include "parentheses.h"

#define MAX_LEN 31

// return 0 - correct, 1 - wrong
int check_parentheses()
{
    struct node *last_el = NULL;
    char str[MAX_LEN];

    printf("Max len of string is %d\n", MAX_LEN-1);
    printf("Input expression:\n|");
    for (int i = 0; i < MAX_LEN-3; i++)
        printf("-");
    printf("|\n");

    scanf("%s", str);
    str[MAX_LEN-1] = '\0';

    for (char *ptr = str; *ptr; ptr++)
    {
        if (*ptr == '(' || *ptr == '[' || *ptr == '{')
            last_el = push_list(last_el, *ptr);
        else if (*ptr == ')' || *ptr == ']' || *ptr == '}')
        {
            if (!last_el)
                return -1;

            if ((*ptr == ')' && last_el->value == '(') || (*ptr == ']' && last_el->value == '[') || (*ptr == '}' && last_el->value == '{'))
                last_el = pop_list(last_el);
            else
                return -1;
        }
    }
    if (last_el)
        return -1;

    return 0;
}
