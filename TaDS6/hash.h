#ifndef TADS6_HASH_H
#define TADS6_HASH_H

typedef struct node_table node_hash;

struct node_table
{
    char *word;
    struct node_table *next;
};

int next_prime_number(int number);
int check_tbl(int *tbl, int len, int max);
int count_min_len(char file_name[], int stop_len_list);
int len_list(node_hash *head);
int next_prime_number(int number);
int key(char *word, int tbl_len);
void insert_node(node_hash **head, node_hash *node);
node_hash* create_hash_node(char *word);
node_hash **create_hash_table(char file_name[], int *len, int stop_len_list);
void remove_from_hash_table(char *del_word, node_hash **table, int len_table, int *done);

void print_table(node_hash **table, int len_table);

#endif //TADS6_HASH_H
