#include <stdio.h>
#include <stdlib.h>
#include "list_stack.h"

static void **free_area;
static int n = 0;

void init_free_area()
{
    free_area = calloc(M, sizeof(void*));
}

// returns address of new last element
struct node* push_list(struct node *last_el, char value)
{
    struct node *tmp = malloc(sizeof(struct node));
    tmp->value = value;
    tmp->previous_el = last_el;

    return tmp;
}

// returns address of new last element
struct node* pop_list(struct node *last_el, int fl_an)
{
    if (last_el == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }

    struct node *tmp = last_el->previous_el;

    if (fl_an)
        free_area[n++] = (void *) last_el;

    free(last_el);

    return tmp;
}

void print_list(struct node *last_el)
{
    if (last_el == NULL)
        printf("List is empty.\n");

    for(; last_el != NULL; last_el = last_el->previous_el)
        printf("%c (%p)\n", last_el->value, last_el);

    printf("\nFree area:\n");
    for(int j = 0; j < n; j++)
        printf("%p ", free_area[j]);
    puts("");
}