#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "constants.h"


struct tree_node* create_node(char *word)
{
    struct tree_node *node;
    node = malloc(sizeof(struct tree_node));

    char *new_word = malloc((SIZE_WORD + 1)*sizeof(char));
    for(int i = 0; word[i]; i++)
        new_word[i] = word[i];
    new_word[strlen(word)] = '\0';

    if (node)
    {
        node->word = new_word;
        node->balance = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void count_node_tree(node_t *tree, int *sum)
{
    if (tree == NULL)
        return;

    *sum += 1;
    count_node_tree(tree->left, sum);
    count_node_tree(tree->right, sum);
}

// обход дерева
void apply_pre(struct tree_node *tree, void (*f)(struct tree_node*, void*, int flag), void *arg, int flag)
{
    if (tree == NULL)
        return;
    f(tree, arg, flag);
    apply_pre(tree->left, f, arg, flag);
    apply_pre(tree->right, f, arg, flag);
}

// визуализация и печать дерева
void to_dot(struct tree_node *tree, void *param, int flag)
{
    FILE *f = param;

    //printf("%d ", tree->balance - flag);

    if (tree->left)
    {
        fprintf(f, "%s -> %s [label = \"left\"];\n", tree->word, tree->left->word);
        // printf("%d %s -> %d %s;", tree->balance, tree->word, tree->left->balance,
        //     tree->left->word);
        printf("%s <- %s;", tree->left->word, tree->word);
    }
    else
        printf("NULL <- %s ", tree->word);

    if (tree->right)
    {
        fprintf(f, "%s -> %s [label = \"right\"];\n", tree->word, tree->right->word);
        //printf(" -> %d %s;\n", tree->right->balance, tree->right->word);
        printf(" -> %s\n", tree->right->word);
    }
    else
        printf(" -> NULL;\n");
}

// трансляция на язык дот
void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree, int flag)
{
    fprintf(f, "digraph %s {\n", tree_name);
    apply_pre(tree, to_dot, f, flag);

    fprintf(f, "}\n");
}
//--------------------------------------------------------------------

// вставка нового узла в обычном дереве
struct tree_node* insert(struct tree_node *tree, struct tree_node *node)
{
    int cmp;

    if (tree == NULL)
        return node;

    cmp = strcmp(node->word, tree->word);
    if (cmp < 0)
    {
        tree->left = insert(tree->left, node);
        fixheight(tree->left);


    }
    else if (cmp > 0)
    {
        tree->right = insert(tree->right, node);
        fixheight(tree->right);
    }
    fixheight(tree);
    return tree;
}

// проверка строки на \n
void check_end (char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n')
            str[i] = '\0';
}

// создание нового дерева
node_t* create_tree(node_t *root, FILE *f)
{
    node_t *node;
    char *word = malloc((SIZE_WORD+1)*sizeof(char));
    while(!feof(f))
    {
        fgets(word, SIZE_WORD, f);
        check_end(word);

        node = create_node(word);
        root = insert(root, node);
    }
    return root;
}

// рассчет высоты узла
int height(node_t* p)
{
    return p ? p->balance : 0;
}

// проверка узла на сбалансированность
int bfactor(node_t* p)
{
    if (height(p->right) == 1 && !p->left)
        return 2;
    else if (height(p->left) == 1 && !p->right)
        return -2;
    else
        return height(p->right)-height(p->left);
}

// пересчет высоты узла после балансировки
void fixheight(node_t* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->balance = (hl>hr?hl:hr)+1;
    //if (!p->left && !p->right)
    //     p->balance = hl;
    //printf("%s %d %d %d\n", p->word, hl, hr, p->balance);
}

// правый поворот
node_t* rotateright(node_t* p) // правый поворот вокруг p
{
    node_t* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

// левый поворот
node_t* rotateleft(node_t* q) // левый поворот вокруг q
{
    node_t* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

// балансировка дерева
node_t* balance(node_t* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p) == 2 )
    {
        if(bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p) == -2 )
    {
        if (bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

// вставка узла в сбалансированное дерево
struct tree_node* bal_insert(struct tree_node *root, struct tree_node *node)
{
    int cmp;

    if (root == NULL)
    {
        return node;
    }
    cmp = strcmp(node->word, root->word);
    if (cmp < 0)
    {
        root->left = bal_insert(root->left, node);
        //fixheight(root);
        root = balance(root);
    }
    else if (cmp > 0)
    {
        root->right = bal_insert(root->right, node);
        //fixheight(root);
        root = balance(root);
    }
    root = balance(root);
    return root;
}

// новый узел в сбалансированном дереве
node_t* create_bal_tree(node_t *root, FILE *f)
{
    node_t *node;
    char *word = malloc((SIZE_WORD+1)*sizeof(char));
    while(!feof(f))
    {
        fgets(word, SIZE_WORD, f);
        check_end(word);

        node = create_node(word);
        root = bal_insert(root, node);
    }
    return root;
}

// удаление в обычном дереве
node_t *remove_in_tree(char *rem, node_t *tree, int *done, int *flag)
{
    int cmp;

    if (tree == NULL)
        return tree;

    cmp = strcmp(rem, tree->word);
    if (!cmp)
    {
        *flag = 1;
        (*done)++;
        if (tree && !tree->left && !tree->right)
        {
            free(tree);
            fixheight(tree);
            return NULL;
        }
        else if (tree && !tree->left && tree->right)
        {
            node_t *replace = tree->right;
            free(tree);
            fixheight(tree);
            return replace;
        }
        else if (tree && tree->left && !tree->right)
        {
            node_t *replace = tree->left;
            free(tree);
            fixheight(tree);
            return replace;
        }
        else
        {
            node_t *cur = tree->right;
            node_t *prev_2 = tree;
            for( ; cur->left; cur = cur->left)
                prev_2 = cur;
            //printf("\\ %s %s\n", cur->word, prev_2->word);

            if (tree == prev_2)
                prev_2->right = prev_2->right->right;
            else
                prev_2->left = NULL;
            //printf("\\ %s %s \n", cur->word, prev_2->word);

            cur->right = insert(cur->right, tree->right);
            cur->left = tree->left;
            node_t *replace = cur;
            fixheight(tree);
            free(tree);
            return replace;

        }

    }
    else if (cmp < 0)
    {
        if (!*flag)
            (*done)++;
        tree->left = remove_in_tree(rem, tree->left, done, flag);
    }
    else if (cmp > 0)
    {
        if (!flag)
            (*done)++;
        tree->right = remove_in_tree(rem, tree->right, done, flag);
    }
    return tree;
}

void check_balance_in_del(node_t *root)
{
    fixheight(root);
    root = balance(root);
}

// удаление в сбалансированном дереве
node_t *remove_in_bal_tree(char *rem, node_t *tree, int *done, int *flag)
{
    int cmp;

    if (tree == NULL)
        return tree;

    cmp = strcmp(rem, tree->word);
    if (!cmp)
    {
        *done = 1;
        if (tree && !tree->left && !tree->right)
        {
            free(tree);
            check_balance_in_del(tree);
            return NULL;
        }
        else if (tree && !tree->left && tree->right)
        {
            node_t *replace = tree->right;
            free(tree);
            check_balance_in_del(tree);
            return replace;
        }
        else if (tree && tree->left && !tree->right)
        {
            node_t *replace = tree->left;
            free(tree);
            check_balance_in_del(tree);
            return replace;
        }
        else
        {
            node_t *cur = tree->left;
            node_t *prev_2 = tree;
            for( ; cur->right; cur = cur->right)
                prev_2 = cur;
            //printf("\\ %s %s\n", cur->word, prev_2->word);

            if (tree == prev_2)
                prev_2->left = prev_2->left->left;
            else
                prev_2->right = NULL;
            //printf("\\ %s %s \n", cur->word, prev_2->word);

            cur->left = insert(cur->left, tree->left);
            cur->right = tree->right;
            node_t *replace = cur;
            check_balance_in_del(tree);
            free(tree);
            return replace;

        }

    }
    else if (cmp < 0)
        tree->left = remove_in_bal_tree(rem, tree->left, done, flag);

    else if (cmp > 0)
        tree->right = remove_in_bal_tree(rem, tree->right, done, flag);

    check_balance_in_del(tree);
    return tree;
}

node_t* findmin(node_t* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?findmin(p->left):p;
}

node_t* removemin(node_t* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node_t* remove_t(node_t* p, char *k, int *done, int *flag) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    int cmp = strcmp(k, p->word);
    if(cmp < 0)
    {
        if (!*flag)
            (*done)++;
        p->left = remove_t(p->left,k, done, flag);
    }
    else if(cmp > 0)
    {
        if (!*flag)
            (*done)++;
        p->right = remove_t(p->right,k, done, flag);
    }
    else //  k == p->key
    {
        (*done)++;
        *flag = 1;
        node_t* q = p->left;
        node_t* r = p->right;
        p->left = NULL;
        p->right = NULL;
        if( !r )
        {
            // fixheight(q);
            return q;
        }
        node_t* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}
