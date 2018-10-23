#ifndef SORT_H
#define SORT_H

#include "structures.h"

unsigned long long tick(void);
void measure_sorting_time();

void swap_students(struct Student *a, struct Student *b);
void mysort_stud(struct Student *base, size_t nitems);
void swap_keys(struct Key *a, struct Key *b);
void mysort_keys(struct Key *base, size_t nitems);

#endif // SORT_H
