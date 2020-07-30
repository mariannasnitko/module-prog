#pragma once
#include <stdlib.h>
#include <stdbool.h>

struct __List
{
    void **items;
    size_t size;
    size_t capacity;
};
typedef struct __List List;

List   *List_alloc      (void);
void    List_free       (List *self);
void    List_init       (List *self);
void    List_deinit     (List *self);

size_t  List_size       (List *self);                           // return number of items in list
void   *List_get        (List *self, int index);                // return self->items[index]
void    List_set        (List *self, int index, void *value);   // set items[index]
void    List_insert     (List *self, int index, void *value);   // insert, shift right
void    List_removeAt   (List *self, int index);                // remove and shift left

void    List_add        (List *self, void *value);     // insert back
void    List_remove     (List *self, void *value);     // remove first by value
int     List_indexOf    (List *self, void *value);     // find index by value
bool    List_contains   (List *self, void *value);     // check by value
bool    List_isEmpty    (List *self);                  // check if list has any items
void    List_clear      (List *self);                  // make list empty