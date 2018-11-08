#ifndef MATRICES_H
#define MATRICES_H

struct IA
{
    int i;
    int Nk;
    struct IA *next;
};

void generate_matrix(int **matr, int n, int m, int fill);
void input_matrix(int **matr, int n, int m);

#endif // MATRICES_H
