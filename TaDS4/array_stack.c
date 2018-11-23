#include "array_stack.h"

int add_to_arr(char **p_curr, char *p_end, char value)
{
    if (*p_curr >= p_end)
    {
        printf("Overflow of array\n");
        return -1;
    }

    (*p_curr)++;
    **p_curr = value;
    return 0;
}

int remove_from_arr(char **p_curr, char *p_beg)
{
    if (*p_curr < p_beg)
        return -1; // Array is empty

    (*p_curr)--;
    return 0;
}

void print_arr(char *p_beg, char *p_curr)
{
    if (p_beg > p_curr)
        printf("Array is empty.\n");

    for(;p_beg <= p_curr; p_beg++)
        printf("%c ", *p_beg);
}