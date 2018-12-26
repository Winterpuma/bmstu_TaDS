#ifndef TADS6_TREE_H
#define TADS6_TREE_H

#include <stdio.h>

typedef struct tree_node node_t;
// узел дерева
struct tree_node
{
    char *word;
    int balance;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node* create_node(char *word);
void count_node_tree(node_t *tree, int *sum);
void apply_pre(struct tree_node *tree, void (*f)(struct tree_node*, void*, int flag), void *arg, int flag);
void to_dot(struct tree_node *tree, void *param, int flag);
void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree, int flag);

struct tree_node* insert(struct tree_node *tree, struct tree_node *node);
void check_end (char *str);

node_t* create_tree(node_t *root, FILE *f);
int height(node_t* p);
int bfactor(node_t* p);
void fixheight(node_t* p);
node_t* rotateright(node_t* p);
node_t* rotateleft(node_t* q);
node_t* balance(node_t* p);
struct tree_node* bal_insert(struct tree_node *root, struct tree_node *node);
node_t* create_bal_tree(node_t *root, FILE *f);

node_t *remove_in_tree(char *rem, node_t *tree, int *done, int *flag);

void check_balance_in_del(node_t *root);
node_t *remove_in_bal_tree(char *rem, node_t *tree, int *done, int *flag);

node_t* findmin(node_t* p);
node_t* removemin(node_t* p);
node_t* remove_t(node_t* p, char *k, int *done, int *flag);



#endif //TADS6_TREE_H
