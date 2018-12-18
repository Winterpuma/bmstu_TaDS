#ifndef TADS5_LIST_H
#define TADS5_LIST_H

#include "structures.h"

node* create_node(char c);
node* add_node(node *head, node *item);
node* pop_node(node **head);

void free_all(node *head);


node* list_push(node* qu, char c, node** used_memory, int *count_used, node** freed_memory, int* count_freed, int* second_used);
node* list_pop(node** qu);
void list_print(node* qu);

void go_list(int n, int interval, time_range t1, time_range t2, time_range t3, time_range t4, int log_flag);

#endif //TADS5_LIST_H
