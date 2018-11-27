#ifndef TADS4_LIST_STACK_H
#define TADS4_LIST_STACK_H

#define M 100

void init_free_area();

struct node
{
    char value;
    struct node *previous_el;
};

struct node* pop_list(struct node *last_el, int fl_an);
struct node* push_list(struct node *last_el, char value);
void print_list(struct node *last_el);

#endif //TADS4_LIST_STACK_H
