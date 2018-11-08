#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "matrices.h"

void allocate_matrix(int **matr, int **A, int **JA, int n, int m)
{
    int size = n * m;
    *matr = calloc(size, sizeof(int));
    *A = malloc(size * sizeof(int));
    *JA = malloc(size * sizeof(int));
}

void allocate_gen_matrix(int **matr, int **A, int **JA, int n, int m, int fill)
{
    int size = n * m;
    *matr = calloc(size, sizeof(int));
    generate_matrix(matr, n, m, fill);
    *A = malloc(size * sizeof(int));
    *JA = malloc(size * sizeof(int));
}

struct IA* create(int i, int num)
{
    //printf("1 in create: %d %d sizeof IA %d\n", i, num, sizeof(struct IA));
    struct IA *node = malloc(sizeof(struct IA));
    if (node)
    {
        node->Nk = num;
        node->i = i;
        node->next = NULL;
    }

    return node;
}

// Функция добавления элемента в стек
struct IA* add(struct IA *node, int i, int num)
{
    struct IA *curr;
    curr = create(i, num);
    if (curr == NULL)
        return NULL;
    node->next = curr;
    return curr;
}

// Освобождение всех эл-тов стека
void free_all(struct IA *head)
{
    struct IA *nxt;

    for (; head; head = nxt)
    {
        nxt = head->next;
        free(head);
    }
}
