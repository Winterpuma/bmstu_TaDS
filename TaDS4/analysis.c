#include <stdio.h>
#include <time.h>

#include "analysis.h"
#include "array_stack.h"
#include "list_stack.h"

#define N 99

unsigned long long tick(void)
{
    unsigned long long tmp;
    __asm__ __volatile__ ("rdtsc" : "=A" (tmp) );
    return tmp;
}

void analise()
{
    unsigned long long duration;
    unsigned long long t1, t2;

    char arrStack[N];
    char *p_curr = arrStack - 1;

    struct node *last_element = NULL;

    printf("PUSH operation:\n");
    t1 = tick();
    for(int i = 0; i < N; i++)
        push_arr(&p_curr, arrStack + N - 1, '1');

    t2 = tick();
    duration = (unsigned long long) (t2-t1);

    printf("\tArray stack: %llu\n", duration);
    t1 = tick();
    for(int i = 0; i < N; i++)
        last_element = push_list(last_element, '1', 0);

    t2 = tick();
    duration = (unsigned long long) (t2-t1);

    printf("\tList stack: %llu\n", duration);

    printf("POP operation:\n");
    t1 = tick();
    for(int i = 0; i < N; i++)
        pop_arr(&p_curr, arrStack);

    t2 = tick();
    duration = (unsigned long long) (t2-t1);
    printf("\tArray stack: %llu\n", duration);

    t1 = tick();
    for(int i = 0; i < N; i++)
        last_element = pop_list(last_element, 0);

    t2 = tick();
    duration = (unsigned long long) (t2-t1);
    printf("\tList stack: %llu\n", duration);
}