#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "efficiency.h"
#include "tree.h"
#include "constants.h"
#include "hash.h"


void menu(void);
int check_int(int *number, int min, int max);
char *input_str(int *error);

int main()
{
    int operation;
    int error = SUCCESS;
    int done;
    int flag;
    int stop_len_list = STOP_LEN_LIST;

    printf("%.2f", 1.20);

    node_t *root = NULL;
    node_t *bal_root = NULL;
    node_hash **table = NULL;
    int len_table = 0;

    unsigned long int time_b, time_e;

    char *del_word = NULL;
    FILE *f;
    f = fopen(DATA_NAME, "r");

    if (!f)
    {
        printf("File with data doesn't exist.");
        return -4;
    }

    root = create_tree(root, f);
    rewind(f);
    bal_root = create_bal_tree(bal_root, f);
    fclose(f);


    while (1)
    {
        menu();
        printf("Option: ");

        if (scanf("%d", &operation) == 1)
        {
            if (!operation)
                break;
            switch(operation)
            {
                case 1:
                {
                    f = fopen(TREE_FILE_NAME, "w");
                    export_to_dot(f, "test_tree", root, 1);
                    //fixheight(root);
                    fclose(f);
                    //system("dot.exe -Tpng tree.gv -o tree.png");
                    //system("C:/msys64/home");
                }
                    break;

                case 2:
                {
                    f = fopen(BAL_TREE_FILE_NAME, "w");
                    export_to_dot(f, "test_tree", bal_root, 0);
                    fclose(f);
                    //system("dot.exe -Tpng bal_tree.gv -o bal_tree.png");
                    //system("C:/msys64/home/"); //to png.
                }
                    break;

                case 3:
                    flag = 0;
                    del_word = input_str(&error);
                    if (error)
                    {
                        printf("Empty string!\n");
                        return -1;
                    }
                    //printf("%s\n", del_word);
                    done = SUCCESS;
                    flag = 0;
                    time_b = tick();
                    root = remove_in_tree(del_word, root, &done, &flag);
                    time_e = tick();
                    if (!flag)
                        printf("No such word!\n");
                    else
                        printf("Word deleted.\n");

                    int count_node = 0;
                    count_node_tree(bal_root, &count_node);
                    int memory = count_node*((sizeof(char*))*3);

                    if (flag)
                        printf("Time removed in tree: %ld clock, employed memory %d bytes\n",
                               time_e - time_b, memory);

                    //bal_root = remove_in_bal_tree(del_word, bal_root, &done);
                    done = SUCCESS;
                    flag = 0;
                    time_b = tick();
                    bal_root = remove_t(bal_root, del_word, &done, &flag);
                    time_e = tick();
                    // count_node_tree(bal_root, &count_node);
                    memory = count_node*((sizeof(char*))*3 + sizeof(int));
                    if (flag)
                        printf("Time removed in balanced tree: %ld clock, employed memory %d bytes\n",
                               time_e - time_b, memory);
                    // bal_root = remove_in_bal_tree(bal_root);
                    break;
                case 4:
                    printf("Input max collision amount [1, 50]: \n");
                    error = check_int(&stop_len_list, 1, 51);

                    if (!error)
                    {
                        printf("Input size of hash table [1, 999]: \n");
                        error = check_int(&len_table, 0, 1000);
                        if (!error)
                            table = create_hash_table(DATA_NAME, &len_table, stop_len_list);
                    }
                    else
                        printf("Wrong number!\n");
                    break;
                case 5:
                    if (!table)
                        printf("Table is empty!!\n");
                    else
                    {
                        printf("\nHash table: \n");
                        print_table(table, len_table);
                    }
                    break;
                case 6:
                    if (!table)
                        printf("Table is empty!!\n");
                    else
                    {
                        del_word = input_str(&error);
                        if (error)
                        {
                            printf("Empty string!\n");
                            return -1;
                        }
                        //printf("%s\n", del_word);
                        done = SUCCESS;
                        remove_from_hash_table(del_word, table, len_table, &done);
                        if (!done)
                            printf("No such word!\n");
                        else
                            printf("Word deleted!\n");
                    }

                    break;
                case 7:
                    //printf("\tFILE:        data10.txt\n");
                    //efficiency("data10.txt", 11);
                    //printf("\tFILE:        data25.txt\n");
                    //efficiency("data25.txt", 30, 3);
                    //printf("\tFILE:        data50.txt\n");
                    //efficiency("data50.txt", 30);
                    printf("\tFILE:        data100alpha.txt\n");
                    efficiency("data25.txt", 30, 3);
                    break;
                default:
                    printf("Input error!\n");
                    break;

            }
            if (!operation)

                break;
        }
        else
            printf("Input error!\n");

    }
    return SUCCESS;
}


void menu(void)
{
    printf("\nChoose option\n"
           "\t0 - Exit\n"
           "\t7 - Efficiency\n"
           "Trees:\n"
           "\t1 - Print tree\n"
           "\t2 - Print balanced tree\n"
           "\t3 - Remove from tree\n"
           "Hash table:\n"
           "\t4 - Create hash table\n"
           "\t5 - Print hash table\n"
           "\t6 - Remove from hash table\n\n");
}

int check_int(int *number, int min, int max)
{
    int rc, num, error;
    char tmp;
    rc = scanf("%d%c", &num, &tmp);
    if (rc == 2 && (tmp == '\n' || tmp == ' '))
    {
        if ((num > min) && (num < max))
        {
            *number = num;
            error = SUCCESS;
        }
        else
            error = ERROR_VALUE;

        if (!min && !max && error == ERROR_VALUE)
        {
            *number = num;
            error = SUCCESS;
        }
        return error;
    }
    else if (tmp != '\n')
    {
        while(tmp != '\n')
            scanf("%c", &tmp);
        return ERROR_INPUT;
    }
    else
        return ERROR_INPUT;

    return SUCCESS;
}


char *input_str(int *error)
{
    *error = SUCCESS;
    char *str = malloc(100*sizeof(char));
    printf("Input word:\n");
    fflush(stdin);
    gets(str);
    check_end(str);
    if (!strlen(str))
        *error = -1;
    return str;
}
