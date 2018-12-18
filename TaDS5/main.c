#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "io.h"
#include "structures.h"
#include "list.h"
#include "q_array.h"


int main()
{
    srand(time(NULL));
    int n = 1000;
    int interval = 100;
    int log = 0;
    time_range T1 = {1, 5};
    time_range T2 = {0, 3};
    time_range T3 = {0, 4};
    time_range T4 = {0, 1};

    int flag = -1;
    while (flag)
    {
        printf("\nChoose option:\n"
               "\t0 - Exit\n"
               "\t1 - Input values\n"
               "\t2 - Print values\n"
               "\t3 - Array queue\n"
               "\t4 - List queue\n");

        fflush(stdin);
        if (scanf("%d", &flag) != 1)
        {
            printf("Wrong input!\n");
            continue;
        }

        switch (flag)
        {
            case 0:
                break;
            case 1:
                input_values(&n, &interval, &log, &T1, &T2, &T3, &T4);
                break;
            case 2:
                print_values(n, interval, log, &T1, &T2, &T3, &T4);
                break;
            case 3:
                go_array(n, interval, T1, T2, T3, T4, log);
                break;
            case 4:
                go_list(n, interval, T1, T2, T3, T4, log);
                break;
            default:
                printf("Wrong input.");
                break;
        }
    }
    return 0;
}
