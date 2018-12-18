#ifndef TADS5_IO_H
#define TADS5_IO_H

#include "structures.h"

void input_values(int *n, int *interval, int *log, time_range *T1, time_range *T2, time_range *T3, time_range *T4);
void input_range(time_range *T, int i);
void print_values(int n, int interval, int log, time_range *T1, time_range *T2, time_range *T3, time_range *T4);
void print_range(time_range *T, int i);

#endif //TADS5_IO_H
