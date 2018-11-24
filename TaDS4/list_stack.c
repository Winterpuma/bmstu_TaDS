#include <stdio.h>
#include <stdlib.h>
#include "list_stack.h"

// returns address of new last element
struct node* add_to_list(struct node *last_el, char value)
{
    struct node *tmp = malloc(sizeof(struct node));
    tmp->value = value;
    tmp->previous_el = last_el;

    return tmp;
}

// returns address of new last element
struct node* remove_from_list(struct node *last_el)
{
    if (last_el == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }

    struct node *tmp = last_el->previous_el;
    free(last_el);

    return tmp;
}

void print_list(struct node *last_el)
{
    if (last_el == NULL)
        printf("List is empty.\n");

    for(; last_el != NULL; last_el = last_el->previous_el)
        printf("%c ", last_el->value);
}