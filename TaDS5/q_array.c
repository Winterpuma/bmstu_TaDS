#include <stdio.h>
#include <time.h>
#include <math.h>

#include "q_array.h"
#include "structures.h"

void arr_push(discriptor* d, char* qu, char c)
{
    char *p_in = d->p_in;
    if (d->p_in == d->p_out && *((char*)d->p_in) != '\0')
        printf("The queue is full.\n");
    else
    {
        *((char*)d->p_in) = c;
        if (d->p_in != d->up)
            d->p_in = p_in + 1;
        else
            d->p_in = d->low;
    }
}


char arr_pop(discriptor* d, char* qu)
{
    char *p_out = d->p_out;
    char ps = '\0';
    if (d->p_in == d->p_out && *((char*)d->p_in) == '\0')
    {
        printf("Empty queue.\n");
    }
    else
    {
        ps = *((char*)d->p_out);
        *((char*)d->p_out) = '\0';
        if (d->p_out != d->up)
            d->p_out = p_out + 1;
        else
            d->p_out = d->low;
    }
    return ps;
}

void arr_print(discriptor* d, char* qu)
{
    if (d->p_in == d->p_out && *((char*)d->p_in) == '\0')
    {
        printf("Empty queue\n");
    }
    else
    {
        printf("Queue: \n");
        char* begin = d->p_out;
        char* end = d->p_in;
        do
        {
            printf("Inf: %c \n", *begin);
            if (begin != d->up)
                begin += 1;
            else
                begin = d->low;
        }
        while(begin != end);
        printf("\n");
    }
}


void go_array(int n, int interval, time_range t1, time_range t2, time_range t3, time_range t4, int log)
{
    char *q1, *q2;
    discriptor d1, d2;

    q1 = (char*)calloc(MAX_LEN, sizeof(char));
    q2 = (char*)calloc(MAX_LEN, sizeof(char));

    init_discriptor_arr(&d1, q1);
    init_discriptor_arr(&d2, q2);

    int type = 1; // Current request type

    double time = 0.0; // Modeling time
    double t_q1 = 0, t_q2 = 0, t_oa = 0;

    // Requests to queue
    int req_in1 = 0, req_in2 = 0, req_out1 = 0, req_out2 = 0;
    int req_show = 0;

    double total_time_out1 = 0;
    double total_time_out2 = 0;

    time_t timer_beg = clock();

    while (req_out1 < n)
    {
        if ((d1.p_in == d1.p_out && *((char*)d1.p_in)) || (d2.p_in == d2.p_out && *((char*)d2.p_in)))
        {
            printf("Queue is full.\n");
            break;
        }

        if (t_q1 == 0)
            t_q1 = rand_time(t1);
        if  (t_q2 == 0)
            t_q2 = rand_time(t2);
        if (t_oa == 0)
        {
            if ((type == 1 || (type == 2 && queue_is_empty(d2))) && !queue_is_empty(d1))
            {
                t_oa = rand_time(t3);
                type = 1;
                arr_pop(&d1, q1);
                upd_dis_del(&d1);
                total_time_out1 += t_oa;
            }
            else if ((type == 2 || (type == 1 && queue_is_empty(d1))) && !queue_is_empty(d2))
            {
                t_oa = rand_time(t4);
                type = 2;
                arr_pop(&d2, q2);
                upd_dis_del(&d2);
                total_time_out2 += t_oa;
            }
        }

        double t_min = 0;

        if(t_oa == 0)
            t_min = fmin(t_q1, t_q2);
        else
            t_min = fmin(t_q1, fmin(t_q2, t_oa));

        // Process requests
        if(t_min == t_oa )
        {
            t_oa = 0;
            if(type == 1)
                req_out1++;
            if(type == 2)
                req_out2++;
        }
        if (req_out1 == n)
            break;

        // Add requests
        if(t_min == t_q1)
        {
            arr_push(&d1, q1, '1');
            upd_dis_add(&d1);
            req_in1++;
        }
        if (t_min == t_q2)
        {
            arr_push(&d2, q2, '2');
            upd_dis_add(&d2);
            req_in2++;
        }

        t_q1 -= t_min;
        t_q2 -= t_min;

        if(t_oa >= t_min)
            t_oa -= t_min;
        time += t_min;

        // Log
        if(req_out1 % interval == 0 && req_out1 != req_show && log)
        {
            req_show = req_out1;
            printf("===============[ %4d ]===================================\n", req_out1);
            printf("\t1 queue: current -  %3d, avg - %3d\n", d1.curr_size, d1.sum_size/d1.out_request);
            printf("\t2 queue: current -  %3d, avg - %3d\n", d2.curr_size, d2.sum_size/d2.out_request);
        }
    }

    time_t timer_end = clock();
    int timer = timer_end - timer_beg;

    puts("\n\n=======================[ Results ]=======================\n");
    printf("Modeling time: %f ticks\n", time);
    printf("In/Out from 1 queue: %d %d (%d)\n", req_in1, req_out1, req_in1 - req_out1);
    printf("In/Out from 2 queue: %d %d (%d)\n", req_in2, req_out2, req_in2 - req_out2);


    double downtime = fabs(time - total_time_out1 - total_time_out2);
    printf("OA downtime: %lf ticks\n\n", downtime);

    double avg_t_in1 = (t1.min + t1.max) / 2;
    double avg_t_out1 = (t3.min + t3.max) / 2;

    double t_modelling = n * fmax(avg_t_in1, avg_t_out1);

    printf("Expected modeling time: %lf\n", t_modelling);
    if (t_modelling > 0)
    {
        double err_out = fabs(100*(time - t_modelling)/t_modelling);
        printf("Out error: %lf%%\n\n", err_out);
    }

    if (timer > 0)
        printf("Time: %d ms\n", timer);
    else
        printf("Time is under 1 ms\n");

    printf("Avg size: %db\n\n", 2*sizeof(char *) + sizeof(char)*MAX_LEN*2);

    free(q1);
    free(q2);
}
