#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "list.h"
#include "deque.h"

void List_print(List *self);
void Deque_print(Deque *self);
void List_read(List *self);

int main(void)
{
    srand(time(NULL));
    List list;
    List llist;
    int temp = 0;
    List_init(&list);
    List_init(&llist);
    List_read(&list);
    for (int i = 0; i < 10; i++)
    {
        List_add(&list, List_get(&list,i));
    }
    List_print(&list);
    int k = List_size(&list);
    printf("List size %d\n", k);
    for (int i = 0; i < List_size(&list); i++)
    {
        if (List_get(&list,i) < 0)
        {
            List_add(&llist, List_get(&list,i));
            temp++;
        }
    }
    for (int i = 0; i < List_size(&list); i++)
    {
        if (List_get(&list,i) >= 0)
        {
            List_add(&llist, List_get(&list,i));
            temp++;
        }
    }
    puts("");
    List_print(&llist);
    List_deinit(&llist);
    puts("");
    Deque deque;
    Deque deque2;
    Deque_init(&deque);
    Deque_init(&deque2);
    for (int i = 0; i < List_size(&list); i++)
    {
        if (i % 2 == 0)
        {
            Deque_pushFront(&deque2, List_get(&list,i));
        }
        else
        {
            Deque_pushBack(&deque, List_get(&list,i));
        }
    }
    puts("");
    Deque_print(&deque);
    puts("");
    Deque_print(&deque2);
    int n = Deque_size(&deque);
    int m = Deque_size(&deque2);
    printf("Deque size %d, %d\n", n, m);
    List list2;
    List_init(&list2);
    Deque_deinit(&deque);
    Deque_deinit(&deque2);
    List_deinit(&list);
    List_deinit(&list2);
    return 0;
}

void List_read(List *self)
{
    //char buf[self->capacity];
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR: file with such name does not exist.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < self->capacity; i++)
    {
        fscanf(fp, "%lf", &self->items[i]);
       // self->items[i] = atof(buf);
    }
    fclose(fp);
}

void List_print(List *self)
{
    for (int i = 0; i < self->size; i++)
    {
        printf("%d). %3.3lf\n", i, self->items[i]);
    }
}

void Deque_print(Deque *self)
{
    for (int i = self->first; i < self->last; i++)
    {
        printf("%d). %3.3lf\n", i, self->items[i]);
    }
}