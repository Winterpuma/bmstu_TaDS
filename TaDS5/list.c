#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "structures.h"

node* create_node(char c)
{
    node *item = malloc(sizeof(node));
    if (item)
    {
        item->inf = c;
        item->next = NULL;
    }
    return item;
}

node* add_node(node *head, node *elem)
{
    elem->next = head;
    return elem;
}

node* pop_node(node **head)
{
    node* back = NULL;
    if (*head != NULL)
    {
        node *cur = (*head);
        if (cur->next)
        {
            for ( ; cur->next->next; cur = cur->next)
                ;
            back = cur->next;
            cur->next = NULL;
        }
        else
        {
            back = cur;
            *head = NULL;
        }
    }
    return back;
}

void free_all(node *head)
{
    node *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

node* list_push(node* qu, char c, node** used_memory, int *count_used, node** freed_memory, int* cnt_freed, int* cnt_reused)
{
    node* item = NULL;
    item = create_node(c);
    if (item)
    {
        used_memory[*(count_used++)] = item;
        int znak = 0;
        for (int i = 0; i < *cnt_freed; i++)
        {
            if (item == freed_memory[i])
            {
                freed_memory[i] = NULL;
                znak = 1;
            }
            if (znak)
                freed_memory[i] = freed_memory[i+1];
        }
        if (znak)
        {
            *cnt_freed -= 1;
            *cnt_reused += 1;
        }
        qu = add_node(qu, item);
    }
    else
        printf("The queue is full.\n");
    return qu;
}

node* list_pop(node** qu)
{
    node* cur = NULL;
    cur = pop_node(qu);
    if (cur == NULL)
        printf("The queue is empty.\n");
    return cur;
}

void list_print(node* qu)
{
    node* cur = qu;
    if (qu == NULL)
    {
        printf("Empty queue\n");
    }
    else
    {
        printf("Current queue: \n");
        for ( ; cur; cur = cur->next)
            printf("Inf: %c\n", cur->inf);
        printf("\n");
    }
}

void go_list(int n, int interval, time_range t1, time_range t2, time_range t3, time_range t4, int log_flag)
{
    node* ret;
    node* freed_memory[MAX_LEN];
    int cnt_freed = 0;
    node* used_memory[MAX_LEN];
    int count_used = 0;
    int cnt_reused = 0;

    node *q1 = NULL, *q2 = NULL;
    discriptor d1, d2;

    init_discriptor(&d1);
    init_discriptor(&d2);

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
        if (d1.curr_size >= MAX_LEN || d2.curr_size >= MAX_LEN)
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
            if ((type == 1 || (type == 2 && q2 == NULL)) && q1)
            {
                t_oa = rand_time(t3);
                type = 1;
                ret = list_pop(&q1);

                if (ret != NULL)
                {
                    freed_memory[cnt_freed++] = ret;
                    free(ret);
                }
                upd_dis_del(&d1);
                total_time_out1 += t_oa;
            }
            else if ((type == 2 || (type == 1 && q1 == NULL)) && q2)
            {
                t_oa = rand_time(t4);
                type = 2;

                ret = list_pop(&q2);
                if (ret != NULL)
                {
                    freed_memory[cnt_freed++] = ret;
                    free(ret);
                }
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
            t_oa = 0.;
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
            q1 = list_push(q1, '1', used_memory, &count_used, freed_memory, &cnt_freed, &cnt_reused);
            upd_dis_add(&d1);
            req_in1++;
        }
        if (t_min == t_q2)
        {
            q2 = list_push(q2, '2', used_memory, &count_used, freed_memory, &cnt_freed, &cnt_reused);
            upd_dis_add(&d2);
            req_in2++;
        }

        t_q1 -= t_min;
        t_q2 -= t_min;


        if(t_oa >= t_min)
            t_oa -= t_min;
        time += t_min;

        // Log
        if(log_flag && (req_out1 % interval == 0) && req_out1 != req_show)
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

    double av_t_in1 = (t1.min + t1.max) / 2;
    double av_t_out1 = (t3.min + t3.max) / 2;

    double t_modelling = n * fmax(av_t_in1, av_t_out1);

    printf("Expected modeling time: %lf\n", t_modelling);
    if (t_modelling > 0)
    {
        double out_err = fabs(100*(time - t_modelling)/t_modelling);
        printf("Out error: %lf%%\n\n", out_err);
    }

    if (timer > 0)
        printf("Time: %d ms\n", timer);
    else
        printf("Time is under 1 ms\n");

    int avg_nodes = (d1.sum_size/d1.out_request) + (d2.sum_size/d2.out_request);
    printf("Avg size: %db\n\n", 2*sizeof(char *) + sizeof(node)*avg_nodes);

    int flag = 0;
    printf("Show memory results? 1-yes/0-no ");
    scanf("%d", &flag);

    if (flag)
    {
        printf("Reused adresses: %d\n", cnt_reused);
        printf("Still free     : %d\n", cnt_freed);
        for (int i = 0; i < fmin(20, cnt_freed); i++)
            printf("%p\n", (void*)freed_memory[i]);
    }

    free_all(q1);
    free_all(q2);
}
