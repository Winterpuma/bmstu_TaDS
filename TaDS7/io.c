#include "head.h"

void print_matr(int **Matr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", Matr[i][j]);
        puts("");
    }
}

int scan_from_file(FILE *f, int **Matr, int n)
{
    for (int i=0; i<n; i++)
    {
        if (feof(f))
            return -1;
        for (int j=0; j<n; j++)
            if (fscanf(f, "%d", *(Matr+i)+j) != 1)
                return -2;
    }

    return 0;
}

void print_graph_file(FILE *out, int **Matr, int n, int *path, int p_l)
{
    fprintf(out, "digraph { \n\trankdir=LR; \n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (Matr[i][j] == 1)
                fprintf(out, "\t%d -> %d;\n", i+1, j+1);

    for (int i = 0; i<p_l-1; i++)
        fprintf(out, "\t%d -> %d[color=blue, penwidth=2.0];", path[i]+1, path[i+1]+1);

    fprintf(out, "}\n");
}
