
#include <stdio.h>
#include "head.h"

int check_files(FILE *f1);

int main()
{
    FILE *f_in, *f_out1, *f_out2;
    int n = 0, **Matr, *path, p_l = 0;

    f_in = fopen(FILE_IN, "r");
    f_out1 = fopen(GRAPH_SIMPLE, "w");
    f_out2 = fopen(GRAPH_PATH, "w");

    if(!(check_files(f_in) && check_files(f_out1) && check_files(f_out2)))
    {
        puts("File error.");
        fclose(f_in);
        fclose(f_out1);
        fclose(f_out2);
        return -1;
    }

    if (fscanf(f_in, "%d", &n) != 1)
    {
        printf("Wrong n in file!\n");
        return -2;
    }
    if (n == 0)
    {
        printf("Empty graph.");
        return 0;
    }

    path = calloc(n, sizeof(int));

    Matr = alloc_rows(n);
    if (Matr == NULL)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    if (scan_from_file(f_in, Matr, n) != 0)
    {
        printf("Wrong values in file!\n");
        free_rows(Matr, n);
        return -1;
    }

    if (empty(Matr, n))
    {
        printf("Can't build graph with no connections.");
        return 0;
    }

    /*
    print_graph_file(f_out1, Matr, n, path, p_l);
    fclose(f_out1);
    system("dot.exe -Tpng graph.dot -o OutputFile.png");
    system("OutputFile.png");*/

    max_path(Matr, n, path, &p_l);

    printf("The longest path:\n -> ");
    for (int i = 0; i < p_l; i++)
        printf("%d -> ", path[i]+1);

    print_graph_file(f_out2, Matr, n, path, p_l);
    fclose(f_out2);
    system("dot.exe -Tpng graph1.dot -o OutputFile1.png");
    system("OutputFile1.png");

    free_rows(Matr, n);
    free(path);
    fclose(f_in);
    return 0;
}


int check_files(FILE *f1)
{
    if (!f1)
        return 0;

    return 1;
}