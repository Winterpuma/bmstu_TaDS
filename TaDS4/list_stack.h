#ifndef TADS4_LIST_STACK_H
#define TADS4_LIST_STACK_H

#define M 100

void init_free_area();

struct node
{
    char value;
    struct node *previous_el;
};

struct node* remove_from_list(struct node *last_el);
struct node* add_to_list(struct node *last_el, char value);
void print_list(struct node *last_el);

#endif //TADS4_LIST_STACK_H
