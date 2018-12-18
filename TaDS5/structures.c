#include "structures.h"

void init_discriptor(discriptor *d)
{
    d->max_num = MAX_LEN;
    d->p_in = NULL;
    d->p_out = NULL;
    d->count_request = 0;
    d->sum_size = 0;
    d->curr_size = 0;
    d->out_request = 0;
    d->in_request = 0;
}

void init_discriptor_arr(discriptor *d, void *q)
{
    init_discriptor(d);
    d->low = q;
    d->up = q + d->max_num;
    d->p_in = q;
    d->p_out = q;
}

// returns 1 if empty
int queue_is_empty(discriptor d)
{
    return ((d.p_in == d.p_out) && (*((char*)d.p_in) == 0));
}

double rand_time(struct time_range t)
{
    return (t.max - t.min) * (rand() / (double)RAND_MAX) + t.min;
}

void upd_dis_del(discriptor *d)
{
    d->curr_size--;
    d->sum_size += d->curr_size;
    d->count_request++;
    d->out_request++;
}

void upd_dis_add(discriptor *d)
{
    d->curr_size++;
    d->sum_size += d->curr_size;
    d->count_request++;
    d->in_request++;
}
