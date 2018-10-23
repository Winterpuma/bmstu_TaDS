#ifndef OPERATIONS_H
#define OPERATIONS_H

void swap(void* a, void* b, void* buf, size_t size);
void bubble_sort(void* base, size_t num, size_t size, int (*compare)(const void*, const void*));
unsigned long long tick(void);
void measure_sorting_time();

#endif // OPERATIONS_H
