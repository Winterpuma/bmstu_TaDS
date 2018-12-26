#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "tree.h"


void print_tbl(int *tbl, int len)
{
    puts("");
    for (int i = 0; i < len; i++)
        printf("%d ", tbl[i]);
    puts("");
}

// 1 - all elements of tbl < max
int check_tbl(int *tbl, int len, int max)
{
    for(int i = 0; i < len; i++)
    {
        if (tbl[i] >=  max)
            return 0;
    }
    return 1;
}

// returns min len of node list
int count_min_len(char file_name[], int stop_len_list)
{
    FILE *f = fopen(file_name, "r");

    int len = 2;
    int *table = calloc(len, sizeof(int));
    char *word = calloc((SIZE_WORD+1), sizeof(char));

    do
    {
        rewind(f);
        len = next_prime_number(len);
        //printf("%d ", len);
        free(table);
        table = calloc(len, sizeof(int));

        while (!feof(f))
        {
            fgets(word, SIZE_WORD, f);
            check_end(word);

            table[key(word, len)]++;

            if (table[key(word, len)] == stop_len_list+1)
                break;
        }
        //print_tbl(table, len);
    }
    while (!check_tbl(table, len, stop_len_list) && len < MAX_LEN_TABLE);

    fclose(f);

    if (len >= MAX_LEN_TABLE)
        return -1;

    return len;
}

int len_list(node_hash *head)
{
    int len = 0;
    for ( ; head; head = head->next)
        len++;
    return len;
}

int next_prime_number(int number)
{
    while (1)
    {
        int count_del = 0;
        number++;
        for(int i = 2; i < number - 1; i++)
            if (!(number%i))
                count_del++;

        if (!count_del)
            return number;
    }
}

int key(char *word, int tbl_len)
{
    int len = strlen(word);
    unsigned int sum = 0;

    for(int i = len - 1; i > -1; i--)
        sum += (word[i] - OFFSET);

    return sum%tbl_len;
}

void insert_node(node_hash **head, node_hash *node)
{
    if (*head)
    {
        node_hash *tmp = *head;
        for (; tmp->next; tmp = tmp->next);
        tmp->next = node;
    }
    else
        *head = node;
}


node_hash* create_hash_node(char *word)
{
    node_hash *node = malloc(sizeof(node_hash));
    char *new_word = malloc((SIZE_WORD + 1)*sizeof(char));

    if (node && new_word)
    {
        for(int i = 0; word[i]; i++)
            new_word[i] = word[i];
        new_word[strlen(word)] = '\0';

        node->word = new_word;
        node->next = NULL;
    }

    return node;
}

node_hash **create_hash_table(char file_name[], int *len, int stop_len_list)
{
    FILE *f;
    node_hash *node;
    char *word = malloc((SIZE_WORD+1)*sizeof(char));

    int min_len = count_min_len(file_name, stop_len_list);

    if (min_len == -1)
    {
        printf("\nCan't create table with length %d, with max nodes %d in list.\n", MAX_LEN_TABLE, stop_len_list);
        printf("Creating table (len (%d))\n", *len);
    }
    else
    {
        printf("Min len is: %d\n", min_len);
        if (*len < min_len)
            *len = min_len;
        printf("Creating table (Len %d)", *len);
    }

    f = fopen(file_name, "r");
    node_hash **table = calloc(*len, sizeof(node_hash *));

    while (!feof(f))
    {
        fgets(word, SIZE_WORD, f);
        check_end(word);

        //print_table(table, *len);
        //printf(" %s", word);

        node = create_hash_node(word);
        insert_node(&(table[key(node->word, *len)]), node);

        //printf("+");
    }

    return table;
}

void print_table(node_hash **table, int len_table)
{
    for (int i = 0; i < len_table; i++)
    {
        printf("%d ", i);
        node_hash *cur= table[i];
        for ( ; cur; cur = cur->next)
        {
            printf (" -> %s", cur->word);
        }
        if (!cur)
            printf(" -> NULL\n");
    }
    printf("\n");
}

void remove_from_hash_table(char *del_word, node_hash **table, int len_table, int *done)
{
    int index = key(del_word, len_table);
    node_hash *cur = table[index];

    int cmp = strcmp(cur->word, del_word);
    if (!cmp)
    {
        table[index] = cur->next;
        free(cur);
        *done = 1;
        return;
    }
    *done = 0;
    node_hash *prev = cur;
    for( ; cur; cur = cur->next)
    {
        (*done)++;
        cmp = strcmp(cur->word, del_word);
        if (!cmp)
        {
            prev->next = cur->next;
            free(cur);
            return;
        }
        prev = cur;
    }
    *done = 0;
}