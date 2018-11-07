#include <stdio.h>
#include <strings.h>
#include "input.h"


int input_flag(char *msg)
{
    int flag = 0;
    char c;
    printf("%s", msg);

    do
    {
        fflush(stdin);
        printf("[y/n]: ");
        scanf("%c", &c);

        if (c == 'y')
            flag = 2;
        else if (c == 'n')
            flag = 1;
    }
    while (!flag);

    return flag-1;
}

void input_size(char *msg, int *n, int *m)
{
    printf("%s", msg);
    fflush(stdin);

    while (scanf("%d %d", n, m) != 2)
    {
        printf("Input ERR. Try again: ");
        fflush(stdin);
    }
}

