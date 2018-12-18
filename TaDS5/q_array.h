#ifndef TADS5_Q_ARRAY_H
#define TADS5_Q_ARRAY_H

#include "structures.h"

void arr_push(discriptor* d, char* qu, char c);
char arr_pop(discriptor* d, char* qu);
void arr_print(discriptor* d, char* qu);

void go_array(int n, int interval, time_range t1, time_range t2, time_range t3, time_range t4, int log_flag);

#endif //TADS5_Q_ARRAY_H
