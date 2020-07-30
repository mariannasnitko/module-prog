#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "list.h"

List *List_alloc(void)
{
    List *list = malloc(sizeof(List));
    List_init(list);
    return list;
}

void List_free(List *self)
{
    List_deinit(self);
    free(self);
}

void List_init(List *self)
{
    self->size = 0;
    self->capacity = 4;
    self->items = malloc(sizeof(void *) * self->capacity);
    if (self->items == NULL)
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}

void List_deinit(List *self)
{
    free(self->items);
}

size_t List_size(List *self)
{
    return self->size;
}

void *List_get(List *self, int index)
{
    return self->items[index];
}

void List_set(List *self, int index, void *value)
{
    self->items[index] = value;
}

void List_insert(List *self, int index, void *value)
{
    if (index > self->size || index < 0)
    {
        fprintf(stderr, "ERROR: item cannot be inserted\n");
        abort();
    }
    else if (index == self->size)
    {
        List_add(self, value);
    }
    else if (index < self->size)
    {
        if (self->size + 1 < self->capacity)
        {
            int newcap = self->capacity + 1;
            void *newitems = realloc(self->items, sizeof(void *) * newcap);
            if (newitems == NULL)
            {
                free(self->items);
                fprintf(stderr, "Reallocating memory error\n");
                abort();
            }
            self->items = newitems;
            self->capacity = newcap;
        }
        for (size_t i = self->size; i >= index; i--)
        {
            self->items[i + 1] = self->items[i - 1];
        }
        self->items[index] = value;
        self->size++;
    }
}

void List_removeAt(List *self, int index)
{
    if (index >= self->size || index < 0)
    {
        printf("ERROR: Index is bigger than list's size\n");
        return;
    }
    free(self->items[index]);
    for (size_t i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size--;
}

void List_add(List *self, void *value)
{
    self->items[self->size] = value;
    self->size += 1;
    if (self->size == self->capacity)
    {
        int newcap = self->capacity * 2;
        void *newitems = realloc(self->items, sizeof(void *) * newcap);
        if (newitems == NULL)
        {
            free(self->items);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        self->items = newitems;
        self->capacity = newcap;
    }
}

void List_remove(List *self, void *value)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (self->items[i] == value)
        {
            free(self->items[i]);
            for (size_t j = i; j < self->size; j++)
            {
                if (j != self->size - 1)
                {
                    self->items[j] = self->items[j + 1];
                }
            }
            self->size--;
            return;
        }
    }
    printf("ERROR: value does not exist\n");
}

int List_indexOf(List *self, void *value)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (self->items[i] == value)
        {
            return i;
        }
    }
    printf("ERROR: value does not exist\n");
    return -1;
}

bool List_contains(List *self, void *value)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (self->items[i] == value)
        {
            return 1;
        }
    }
    return 0;
}

bool List_isEmpty(List *self)
{
    if (self->size == 0)
        return 1;
    else
        return 0;
}

void List_clear(List *self)
{
    self->size = 0;
}