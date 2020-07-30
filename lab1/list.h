#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct __List
{
    double *items;   
    size_t capacity; 
    size_t size;     
};
typedef struct __List List;

void    List_init       (List *self);   // allocate items, set capacity and size
void    List_deinit     (List *self);   // free allocated items
List   *List_alloc      (void);         // allocate new List on heap, init it
void    List_free       (List *self);   // deinit self, free it

size_t  List_size       (List *self);                          // return number of items in list
double  List_get        (List *self, int index);               // return self->items[index]
void    List_set        (List *self, int index, double value); // set self->items[index]
void    List_insert     (List *self, int index, double value); // insert, shift right
void    List_removeAt   (List *self, int index);               // remove and shift left

void    List_add        (List *self, double value);     // insert back
void    List_remove     (List *self, double value);     // remove first by value
int     List_indexOf    (List *self, double value);     // find index by value
bool    List_contains   (List *self, double value);     // check by value
bool    List_isEmpty    (List *self);                   // check if list has any items
void    List_clear      (List *self);                   // make list empty