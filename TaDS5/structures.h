#ifndef TADS5_STRUCTURES_H
#define TADS5_STRUCTURES_H

#include <stdlib.h>


#define MAX_LEN 10000

struct time_range
{
    double min;
    double max;
};
typedef struct time_range time_range;

typedef struct discriptor discriptor;
struct discriptor
{
    void* low;
    void* up;
    void* p_in;
    void* p_out;
    int max_num;
    int count_request;
    int sum_size;
    int curr_size;
    int out_request;
    int in_request;
};

typedef struct node node;
struct node
{
    char inf;
    node *next;
};

void init_discriptor(discriptor *d);
void init_discriptor_arr(discriptor *d, void *q);
void upd_dis_del(discriptor *d);
void upd_dis_add(discriptor *d);

int queue_is_empty(discriptor d);

double rand_time(struct time_range t);

#endif //TADS5_STRUCTURES_H
