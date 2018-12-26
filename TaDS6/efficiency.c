#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "efficiency.h"
#include "tree.h"
#include "constants.h"
#include "hash.h"


int deleted_in_file(int number)
{
    int len = 0;
    FILE *f1 = fopen("data_copy.txt", "r");
    FILE *f2 = fopen("data_copy_2.txt", "w");
    char *word = malloc((SIZE_WORD+1)*sizeof(char));
    int count = 0;

    while(!feof(f1))
    {
        fgets(word, SIZE_WORD, f1);
        len += strlen(word);
        if (count != number)
            fprintf(f2, "%s", word);

        count++;
    }
    fclose(f1);
    fclose(f2);

    f1 = fopen("data_copy.txt", "w");
    f2 = fopen("data_copy_2.txt", "r");
    while(!feof(f2))
    {
        fgets(word, SIZE_WORD, f2);
        fprintf(f1, "%s", word);
    }

    fclose(f1);
    fclose(f2);

    return len;
}

void efficiency(char data_file[], int len_table, int stop_len_list)
{
    FILE *f = fopen(data_file, "r");

    if (!f)
    {
        printf("File %s doesn't exist\n", data_file);
        return;
    }

    int start = time(NULL);
    srand(start);
    unsigned long int time_b, time_e;
    unsigned long int time_tree = 0, time_bal_tree = 0, time_hash = 0,
            time_file = 0;
    double count_tree = 0, count_bal_tree = 0, count_hash = 0,
            count_file = 0;

    node_t *root = NULL;
    node_t *bal_root = NULL;
    node_hash **table = NULL;

    int done;
    int len_file;

    root = create_tree(root, f);
    rewind(f);
    bal_root = create_bal_tree(bal_root, f);
    fclose(f);

    table = create_hash_table(data_file, &len_table, stop_len_list);

    f = fopen(data_file, "r");
    FILE *f2 = fopen("data_copy.txt", "w");

    char *word = malloc((SIZE_WORD+1)*sizeof(char));
    while(!feof(f))
    {
        fgets(word, SIZE_WORD, f);
        fprintf(f2, "%s", word);
    }
    fclose(f);
    fclose(f2);

    int count_node = 0;
    count_node_tree(bal_root, &count_node);
    int memory_tree = count_node*((sizeof(char*))*3);
    int memory_bal_tree = count_node*((sizeof(char*))*3 + sizeof(int));
    //int memory_hash = (int)table;//create_hash_table(table, len_table);

    printf("+\n");
    int flag = 0;
    int len = 0;
    int count_word = COUNT_WORD;
    int words_total = 0;

    f = fopen(data_file, "r");
    while(!feof(f)) {
        fgets(word, SIZE_WORD, f);
        words_total++;
    }
    fclose(f);

    for (int i = 0; i < COUNT_DELETED; i++)
    {
        int number = rand()%count_word;
        int count = 0;
        //printf("number %d\n", number);
        f = fopen("data_copy.txt", "r");
        while(!feof(f))
        {
            fgets(word, SIZE_WORD, f);
            check_end(word);
            if (count == number)
                break;
            count++;
        }
        fclose(f);
        //printf("%s\n", word);

        done = 0;
        flag = 0;
        time_b = tick();
        root = remove_in_tree(word, root, &done, &flag);
        time_e = tick();
        time_tree += time_e - time_b;
        count_tree += done;
        done = 0;
        //printf("+\n");

        flag = 0;
        time_b = tick();
        bal_root = remove_t(bal_root, word, &done, &flag);
        time_e = tick();
        time_bal_tree += time_e - time_b;
        count_bal_tree += done;
        done = 0;
        //printf("+\n");

        time_b = tick();

        remove_from_hash_table(word, table, len_table, &done);
        time_e = tick();
        time_hash += time_e - time_b;
        //print_table(table, len_table);
        count_hash += done;
        done = 0;
        //printf("+\n");

        time_b = tick();
        len_file = deleted_in_file(number);
        time_e = tick();
        if (!len)
            len = len_file;
        time_file += time_e - time_b;
        count_file += number;

        done = 0;
        count_word--;
    }



    printf("\n");

    printf("|                      |");
    printf("     tree      |");
    printf(" balanced tree |");
    printf("   hash table  |\n");


    for (int i = 0; i < COUNT_SPACE; i++)
        printf("-");
    printf("\n");

    printf("|   time (clock)       |");
    printf("     %8ld  |", time_tree/COUNT_DELETED);
    printf("     %8ld  |", time_bal_tree/COUNT_DELETED);
    printf("     %8ld  |\n", time_hash/COUNT_DELETED);

    printf("|   memory (bites)     |");
    printf("     %8d  |", memory_tree + len_file);
    printf("     %8d  |", memory_bal_tree + len_file);
    printf("     %8llu  |\n", sizeof(struct node_table)*words_total + len_file + sizeof(struct node_hash *));


    printf("| count of comparisons |");
    printf("     %8.2lf  |", count_tree/COUNT_DELETED);
    printf("     %8.2lf  |", count_bal_tree/COUNT_DELETED);
    printf("     %8.2lf  |\n", count_hash/COUNT_DELETED);

    printf("\n");

}

unsigned long int tick(void)
{
    unsigned long int d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}