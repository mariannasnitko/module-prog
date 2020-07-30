#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "strstrmap.h"
#include "list.h"

StrStrMap *StrStrMap_alloc()
{
    StrStrMap *new = malloc(sizeof(StrStrMap));
    if (new == NULL)
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
    StrStrMap_init(new);
    return new;
}

void StrStrMap_init(StrStrMap *self)
{
    self->capacity = 16;
    self->items = malloc(sizeof(KeyValue) * self->capacity);
    if (self->items == NULL)
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
    self->size = 0;
}

void StrStrMap_deinit(StrStrMap *self)
{
    free(self->items);
}

void StrStrMap_free(StrStrMap *self)
{
    StrStrMap_deinit(self);
    free(self);
}

size_t StrStrMap_size(StrStrMap *self)
{
    return self->size;
}

bool StrStrMap_contains(StrStrMap *self, const char *key)
{
    for (size_t i = 0; i < StrStrMap_size(self); i++)
    {
        if (self->items[i].key == key)
            return 1;
    }
    return 0;
}

void StrStrMap_add(StrStrMap *self, const char *key, const char *value)
{
    self->items[self->size].key = key;
    self->items[self->size].value = value;
    self->size += 1;
    if (self->size == self->capacity)
    {
        int newcap = self->capacity * 2;
        KeyValue *newitems = realloc(self->items, sizeof(KeyValue) * newcap);
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

const char *StrStrMap_get(StrStrMap *self, const char *key)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (strcmp(self->items[i].key, key) == 0)
        {
            return self->items[i].value;
        }
    }
    return NULL;
}

const char *StrStrMap_set(StrStrMap *self, const char *key, const char *value)
{
    const char *oldValue = NULL;
    for (size_t i = 0; i < StrStrMap_size(self); i++)
    {
        if (strcmp(self->items[i].key, key) == 0)
        {
            oldValue = self->items[i].value;
            self->items[i].value = value;
        }
    }
    return oldValue;
}

const char *StrStrMap_remove(StrStrMap *self, const char *key)
{
    const char *oldValue = NULL;
    for (size_t i = 0; i < StrStrMap_size(self); i++)
    {
        if (strcmp(self->items[i].key, key) == 0)
        {
            oldValue = self->items[i].value;
            for (size_t j = i; j < StrStrMap_size(self) - 1; j++)
            {
                self->items[j] = self->items[j + 1];
            }
            self->size -= 1;
        }
    }
    return oldValue;
}

void StrStrMap_clear(StrStrMap *self)
{
    for (size_t j = 0; j < StrStrMap_size(self); j++)
    {
        free((char *)self->items[j].value);
    }
    StrStrMap_free(self);
}

void StrStrMap_keys(StrStrMap *self, List *keys)
{
    for (size_t i = 0; i < StrStrMap_size(self); i++)
    {
        List_add(keys, (void *)self->items[i].key);
    }
}

void StrStrMap_values(StrStrMap *self, List *values)
{
    for (size_t i = 0; i < StrStrMap_size(self); i++)
    {
        List_add(values, (void *)self->items[i].value);
    }
}