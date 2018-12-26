#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "in3.txt"
#define GRAPH_SIMPLE "graph.dot"
#define GRAPH_PATH "graph1.dot"

int** alloc_rows(int n);
void free_rows(int **data, int n);

void print_matr(int **matr, int n);
int scan_from_file(FILE *f, int **matr, int n);
void print_graph_file(FILE *out, int **matr, int n, int *path, int p_l);

int empty(int **matr, int n);
int max_path(int **matr, int n, int *path, int *p_l);
int obhod(int **matr, int n, int num, int *Q, int *q_l, int *M, int *path, int *p_l);
int find_int(int *Q, int n, int i);

#endif // HEAD_H
